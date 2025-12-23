/*
**	swf2apt
**	Copyright 2025 Jonathan Wilson
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

using SwfLib.Tags.BitmapTags;
using System;
using System.IO;
using System.Runtime.InteropServices;
using TGASharpLib;

namespace eaf2apt.Characters
{
    unsafe struct JpegOutput
    {
        public uint output_width;
        public uint output_height;
        public int output_components;
        public byte* outbuffer;
        public int outsize;
    };
    class AptCharacterBitmap : AptCharacter
    {
        [DllImport("jpeg.dll", EntryPoint = "DecodeJpeg", CallingConvention = CallingConvention.Cdecl)]
        unsafe static extern JpegOutput* DecodeJpeg(byte* buffer, int size);

        [DllImport("jpeg.dll", EntryPoint = "FreeJpeg", CallingConvention = CallingConvention.Cdecl)]
        unsafe static extern void FreeJpeg(JpegOutput* buffer);

        public string TextureName;
        public string JpegName;
        public bool HasJpeg = false;
        public bool NoPack = false;
        public ushort Width = 0;
        public ushort Height = 0;
        public override void OutputCharacter(int i)
        {
            base.OutputCharacter(i);
            GlobalData.output.Write(3, (int)AptCharacterType.Bitmap);
            GlobalData.output.Write(3, 0x09876543);

            if (GlobalData.IsTT)
            {
                GlobalData.output.Write(3, 0x0);
                GlobalData.output.Write(3, 0x0);
            }

            GlobalData.output.Write(3, ID);
        }
        public void Unpremultiply(byte[] data, uint width, uint height)
        {
            for (var i = 0; i < height * width; i++)
            {
                var alpha = data[(i * 4)];
                var red = data[(i * 4) + 1];
                var green = data[(i * 4) + 2];
                var blue = data[(i * 4) + 3];
                var newalpha = Math.Max(alpha, (byte)1);
                data[(i * 4)] = (byte)(Math.Min(blue * 255.0f / newalpha, 255.0f));
                data[(i * 4) + 1] = (byte)(Math.Min(green * 255.0f / newalpha, 255.0f));
                data[(i * 4) + 2] = (byte)(Math.Min(red * 255.0f / newalpha, 255.0f));
                data[(i * 4) + 3] = alpha;
            }
        }
        public AptCharacterBitmap(byte[] data, ushort width, ushort height, Globals globaldata, int id) : base(globaldata, id)
        {
            Width = width;
            Height = height;
            TextureName = @$"{globaldata.texturesdir}\{id}.tga";
            var tga = new TGA(width, height, TgaPixelDepth.Bpp32, TgaImageType.Uncompressed_TrueColor, 0, false);
            tga.Header.ColorMapSpec.ColorMapEntrySize = TgaColorMapEntrySize.A8R8G8B8;
            tga.ImageOrColorMapArea.ImageData = data;

            if (GlobalData.IsRA3)
            {
                tga.Header.ImageSpec.ImageDescriptor.ImageOrigin = TgaImgOrigin.TopLeft;
                tga.Header.ImageSpec.ImageDescriptor.AlphaChannelBits = 0;
            }
            else
            {
                tga.Header.ImageSpec.ImageDescriptor.ImageOrigin = TgaImgOrigin.BottomLeft;
                tga.Header.ImageSpec.ImageDescriptor.AlphaChannelBits = 8;
            }

            tga.Save(TextureName);
        }
        public AptCharacterBitmap(DefineBitsLosslessTag tag, Globals globaldata) : base(globaldata, tag.CharacterID)
        {
            TextureName = @$"{globaldata.texturesdir}\{tag.CharacterID}.tga";
            var uncompdata = SwfLib.SwfZip.DecompressZlib(tag.ZlibBitmapData);

            if (tag.BitmapFormat == 5)
            {
                var data = new byte[tag.BitmapHeight * tag.BitmapWidth * 4];

                for (var i = 0; i < tag.BitmapHeight; i++)
                {
                    int outpos = i * tag.BitmapWidth * 4;
                    int inpos = (tag.BitmapHeight - i - 1) * tag.BitmapWidth * 4;

                    for (var j = 0; j < tag.BitmapWidth * 4; j++)
                    {
                        data[outpos + j] = uncompdata[inpos + j];
                    }
                }

                Unpremultiply(data, tag.BitmapWidth, tag.BitmapHeight);
                Width = tag.BitmapWidth;
                Height = tag.BitmapHeight;

                if (!GlobalData.IsRA3)
                {
                    var newdata = new byte[tag.BitmapHeight * tag.BitmapWidth * 3];

                    for (var i = 0; i < tag.BitmapHeight * tag.BitmapWidth; i++)
                    {
                        newdata[(i * 3)] = data[(i * 4)];
                        newdata[(i * 3) + 1] = data[(i * 4) + 1];
                        newdata[(i * 3) + 2] = data[(i * 4) + 2];
                    }

                    var tga = new TGA(tag.BitmapWidth, tag.BitmapHeight, TgaPixelDepth.Bpp24, TgaImageType.Uncompressed_TrueColor, 0, false);
                    tga.Header.ColorMapSpec.ColorMapEntrySize = TgaColorMapEntrySize.A8R8G8B8;
                    tga.ImageOrColorMapArea.ImageData = newdata;
                    tga.Save(TextureName);
                }
                else
                {
                    var newdata = new byte[tag.BitmapHeight * tag.BitmapWidth * 4];

                    for (var i = 0; i < tag.BitmapHeight * tag.BitmapWidth; i++)
                    {
                        newdata[(i * 4)] = data[(i * 4)];
                        newdata[(i * 4) + 1] = data[(i * 4) + 1];
                        newdata[(i * 4) + 2] = data[(i * 4) + 2];
                        newdata[(i * 4) + 3] = 0xFF;
                    }

                    var tga = new TGA(tag.BitmapWidth, tag.BitmapHeight, TgaPixelDepth.Bpp32, TgaImageType.Uncompressed_TrueColor, 8, false);
                    tga.Header.ColorMapSpec.ColorMapEntrySize = TgaColorMapEntrySize.A8R8G8B8;
                    tga.ImageOrColorMapArea.ImageData = newdata;
                    tga.Save(TextureName);
                }
            }
            else
            {
                throw new NotSupportedException("Unsupported Image Format");
            }
        }
        public AptCharacterBitmap(DefineBitsLossless2Tag tag, Globals globaldata) : base(globaldata, tag.CharacterID)
        {
            TextureName = @$"{globaldata.texturesdir}\{tag.CharacterID}.tga";
            var uncompdata = SwfLib.SwfZip.DecompressZlib(tag.ZlibBitmapData);

            if (tag.BitmapFormat == 5)
            {
                var data = new byte[uncompdata.Length];

                for (var i = 0; i < tag.BitmapHeight; i++)
                {
                    int outpos = i * tag.BitmapWidth * 4;
                    int inpos = (tag.BitmapHeight - i - 1) * tag.BitmapWidth * 4;

                    for (var j = 0; j < tag.BitmapWidth * 4; j++)
                    {
                        data[outpos + j] = uncompdata[inpos + j];
                    }
                }

                Unpremultiply(data, tag.BitmapWidth, tag.BitmapHeight);
                Width = tag.BitmapWidth;
                Height = tag.BitmapHeight;
                var tga = new TGA(tag.BitmapWidth, tag.BitmapHeight, TgaPixelDepth.Bpp32, TgaImageType.Uncompressed_TrueColor, 8, false);
                tga.Header.ColorMapSpec.ColorMapEntrySize = TgaColorMapEntrySize.A8R8G8B8;
                tga.ImageOrColorMapArea.ImageData = data;
                tga.Save(TextureName);
            }
            else
            {
                throw new NotSupportedException("Unsupported Image Format");
            }
        }
        unsafe public AptCharacterBitmap(DefineBitsTag tag, Globals globaldata) : base(globaldata, tag.CharacterID)
        {
            HasJpeg = true;
            JpegName = @$"{globaldata.texturesdir}\{tag.CharacterID}.jpg";
            FileStream stream = new FileStream(JpegName, FileMode.CreateNew);
            stream.Write(tag.JPEGData, 0, 20);

            if (globaldata.JPEGTables.Length > 0)
            {
                stream.Write(globaldata.JPEGTables, 2, globaldata.JPEGTables.Length - 4);
            }

            stream.Write(tag.JPEGData, 20, tag.JPEGData.Length - 20);
            stream.Close();
            MemoryStream mem = new MemoryStream();
            mem.Write(tag.JPEGData, 0, 20);

            if (globaldata.JPEGTables.Length > 0)
            {
                mem.Write(globaldata.JPEGTables, 2, globaldata.JPEGTables.Length - 4);
            }

            mem.Write(tag.JPEGData, 20, tag.JPEGData.Length - 20);
            mem.Close();

            if (GlobalData.IsTT)
            {
                TextureName = @$"{globaldata.texturesdir}\{tag.CharacterID}.tga";
                JpegOutput* output;

                fixed (byte* ptr = mem.ToArray())
                {
                    output = DecodeJpeg(ptr, mem.ToArray().Length);
                }

                TgaImageType type = TgaImageType.Uncompressed_TrueColor;
                Width = (ushort)output->output_width;
                Height = (ushort)output->output_height;
                var tga = new TGA((ushort)output->output_width, (ushort)output->output_height, TgaPixelDepth.Bpp32, type, 8, false);
                tga.Header.ColorMapSpec.ColorMapEntrySize = TgaColorMapEntrySize.A8R8G8B8;
                byte[] data = new byte[output->output_width * output->output_height * 4];
                byte[] idata = new byte[output->outsize];
                Span<byte> span = new Span<byte>(output->outbuffer, output->outsize);
                Span<byte> arrayspan = new Span<byte>(idata);
                span.CopyTo(arrayspan);

                for (int i = 0; i < output->output_width * output->output_height; i++)
                {
                    byte alpha = 0xFF;
                    data[(i * 4)] = idata[(i * 3) + 2];
                    data[(i * 4) + 1] = idata[(i * 3) + 1];
                    data[(i * 4) + 2] = idata[(i * 3)];
                    data[(i * 4) + 3] = alpha;
                }

                var data2 = new byte[data.Length];

                for (var i = 0; i < output->output_height; i++)
                {
                    int outpos = i * (int)output->output_width * 4;
                    int inpos = ((int)output->output_height - i - 1) * (int)output->output_width * 4;
                    for (var j = 0; j < output->output_width * 4; j++)
                    {
                        data2[outpos + j] = data[inpos + j];
                    }
                }

                tga.ImageOrColorMapArea.ImageData = data2;
                tga.Save(TextureName);
                FreeJpeg(output);
            }
        }
        unsafe public AptCharacterBitmap(DefineBitsJPEG2Tag tag, Globals globaldata) : base(globaldata, tag.CharacterID)
        {
            HasJpeg = true;
            JpegName = @$"{globaldata.texturesdir}\{tag.CharacterID}.jpg";
            using FileStream stream = new FileStream(JpegName, FileMode.CreateNew);

            if (tag.ImageData[0] == 0xff && tag.ImageData[1] == 0xd9 && tag.ImageData[2] == 0xff && tag.ImageData[3] == 0xd8)
            {
                stream.Write(tag.ImageData, 4, tag.ImageData.Length - 4);
            }
            else
            {
                stream.Write(tag.ImageData, 0, tag.ImageData.Length);
            }

            stream.Close();
            MemoryStream mem = new MemoryStream();

            if (tag.ImageData[0] == 0xff && tag.ImageData[1] == 0xd9 && tag.ImageData[2] == 0xff && tag.ImageData[3] == 0xd8)
            {
                mem.Write(tag.ImageData, 4, tag.ImageData.Length - 4);
            }
            else
            {
                mem.Write(tag.ImageData, 0, tag.ImageData.Length);
            }

            mem.Close();

            if (GlobalData.IsTT)
            {
                TextureName = @$"{globaldata.texturesdir}\{tag.CharacterID}.tga";
                JpegOutput* output;

                fixed (byte* ptr = mem.ToArray())
                {
                    output = DecodeJpeg(ptr, mem.ToArray().Length);
                }

                TgaImageType type = TgaImageType.Uncompressed_TrueColor;
                Width = (ushort)output->output_width;
                Height = (ushort)output->output_height;
                var tga = new TGA((ushort)output->output_width, (ushort)output->output_height, TgaPixelDepth.Bpp32, type, 8, false);
                tga.Header.ColorMapSpec.ColorMapEntrySize = TgaColorMapEntrySize.A8R8G8B8;
                byte[] data = new byte[output->output_width * output->output_height * 4];
                byte[] idata = new byte[output->outsize];
                Span<byte> span = new Span<byte>(output->outbuffer, output->outsize);
                Span<byte> arrayspan = new Span<byte>(idata);
                span.CopyTo(arrayspan);

                for (int i = 0; i < output->output_width * output->output_height; i++)
                {
                    byte alpha = 0xFF;
                    data[(i * 4)] = idata[(i * 3) + 2];
                    data[(i * 4) + 1] = idata[(i * 3) + 1];
                    data[(i * 4) + 2] = idata[(i * 3)];
                    data[(i * 4) + 3] = alpha;
                }

                var data2 = new byte[data.Length];

                for (var i = 0; i < output->output_height; i++)
                {
                    int outpos = i * (int)output->output_width * 4;
                    int inpos = ((int)output->output_height - i - 1) * (int)output->output_width * 4;

                    for (var j = 0; j < output->output_width * 4; j++)
                    {
                        data2[outpos + j] = data[inpos + j];
                    }
                }

                tga.ImageOrColorMapArea.ImageData = data2;
                tga.Save(TextureName);
                FreeJpeg(output);
            }
        }
        unsafe public AptCharacterBitmap(DefineBitsJPEG3Tag tag, Globals globaldata) : base(globaldata, tag.CharacterID)
        {
            TextureName = @$"{globaldata.texturesdir}\{tag.CharacterID}.tga";
            MemoryStream mem = new MemoryStream();

            if (tag.ImageData[0] == 0xff && tag.ImageData[1] == 0xd9 && tag.ImageData[2] == 0xff && tag.ImageData[3] == 0xd8)
            {
                mem.Write(tag.ImageData, 4, tag.ImageData.Length - 4);
            }
            else
            {
                for (int i = 0; i < tag.ImageData.Length - 1; i++)
                {
                    if (tag.ImageData[i] == 0xFF)
                    {
                        if (tag.ImageData[i + 1] == 0xD9)
                        {
                            if (i + 2 == tag.ImageData.Length)
                            {
                                mem.Write(tag.ImageData, 0, tag.ImageData.Length);
                            }
                            else
                            {
                                mem.Write(tag.ImageData, i + 2, 20);
                                mem.Write(tag.ImageData, 2, i - 2);
                                mem.Write(tag.ImageData, i + 22, tag.ImageData.Length - (i + 24));
                            }
                            break;
                        }
                    }
                }
            }

            mem.Seek(0, SeekOrigin.Begin);
            var uncompdata = SwfLib.SwfZip.DecompressZlib(tag.BitmapAlphaData);
            JpegOutput *output;

            fixed (byte* ptr = mem.ToArray())
            {
                output = DecodeJpeg(ptr, mem.ToArray().Length);
            }

            TgaImageType type = TgaImageType.Uncompressed_TrueColor;

            if (GlobalData.IsRA3)
            {
                type = TgaImageType.RLE_TrueColor;
            }

            Width = (ushort)output->output_width;
            Height = (ushort)output->output_height;
            var tga = new TGA((ushort)output->output_width, (ushort)output->output_height, TgaPixelDepth.Bpp32, type, 8, false);
            tga.Header.ColorMapSpec.ColorMapEntrySize = TgaColorMapEntrySize.A8R8G8B8;
            byte[] data = new byte[output->output_width * output->output_height * 4];
            byte[] idata = new byte[output->outsize];
            Span<byte> span = new Span<byte>(output->outbuffer, output->outsize);
            Span<byte> arrayspan = new Span<byte>(idata);
            span.CopyTo(arrayspan);

            for (int i = 0; i < output->output_width * output->output_height; i++)
            {
                byte alpha = uncompdata[i];
                data[(i * 4) + 3] = idata[(i * 3) + 2];
                data[(i * 4) + 2] = idata[(i * 3) + 1];
                data[(i * 4) + 1] = idata[(i * 3)];
                data[(i * 4)] = alpha;
            }

            Unpremultiply(data, output->output_width, output->output_height);
            var data2 = new byte[data.Length];

            for (var i = 0; i < output->output_height; i++)
            {
                int outpos = i * (int)output->output_width * 4;
                int inpos = ((int)output->output_height - i - 1) * (int)output->output_width * 4;
                for (var j = 0; j < output->output_width * 4; j++)
                {
                    data2[outpos + j] = data[inpos + j];
                }
            }

            tga.ImageOrColorMapArea.ImageData = data2;
            tga.Save(TextureName);
            FreeJpeg(output);
        }
    }
}
