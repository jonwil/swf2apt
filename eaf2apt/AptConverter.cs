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

using eaf2apt.Characters;
using SwfLib;
using SwfLib.Tags;
using SwfLib.Tags.BitmapTags;
using SwfLib.Tags.ButtonTags;
using SwfLib.Tags.ControlTags;
using SwfLib.Tags.FontTags;
using SwfLib.Tags.ShapeMorphingTags;
using SwfLib.Tags.ShapeTags;
using SwfLib.Tags.SoundTags;
using SwfLib.Tags.TextTags;
using SwfLib.Tags.VideoTags;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Runtime.InteropServices;
using System.Text;
using System.Text.RegularExpressions;
using TGASharpLib;

namespace eaf2apt
{
    enum ConstPointerType
    {
        imports = 0,
        exports = 1,
        characters = 2,
        maincharacter = 3
    };
    class TextureEntry
    {
        public int MapsTo;
        public int OffsetX;
        public int OffsetY;
        public int OrigWidth;
        public int OrigHeight;
        public int Width;
        public int Height;
        public bool rotated;
    }
    class AptConverter
    {
        Globals GlobalData;
        List<AptCharacterBitmap> bitmaps = new();
        List<AptCharacterShape> shapes = new();
        List<string> NoPackedStrings = new();
        List<string> ShapeIDs = new();
        Dictionary<int, TextureEntry> textures = new();

        [DllImport("kernel32.dll", CharSet = CharSet.Auto, SetLastError = true)]
        static extern uint GetShortPathName(
            [MarshalAs(UnmanagedType.LPTStr)]
            string lpszLongPath,
            [MarshalAs(UnmanagedType.LPTStr)]
            StringBuilder lpszShortPath,
            uint cchBuffer);
        [DllImport("jpeg.dll", EntryPoint = "GetCharHashTable", CallingConvention = CallingConvention.Cdecl)]
        static extern IntPtr GetCharHashTable();
        [DllImport("jpeg.dll", EntryPoint = "FreeCharHashTable", CallingConvention = CallingConvention.Cdecl)]
        static extern void FreeCharHashTable(IntPtr table);
        [DllImport("jpeg.dll", EntryPoint = "StoreCharEntry", CallingConvention = CallingConvention.Cdecl)]
        static extern void StoreCharEntry(IntPtr table, String key, String value);
        [DllImport("jpeg.dll", EntryPoint = "ResetCharIterator", CallingConvention = CallingConvention.Cdecl)]
        static extern int ResetCharIterator(IntPtr table);
        [DllImport("jpeg.dll", EntryPoint = "GetCharValue", CallingConvention = CallingConvention.Cdecl)]
        static extern IntPtr GetCharValue(IntPtr table);
        [DllImport("jpeg.dll", EntryPoint = "GetCharKey", CallingConvention = CallingConvention.Cdecl)]
        static extern IntPtr GetCharKey(IntPtr table);
        [DllImport("jpeg.dll", EntryPoint = "CopyCharHashTable", CallingConvention = CallingConvention.Cdecl)]
        static extern IntPtr CopyCharHashTable(IntPtr table);
        [DllImport("jpeg.dll", EntryPoint = "FormatDoubleG", CallingConvention = CallingConvention.Cdecl)]
        unsafe static extern IntPtr FormatDoubleG(int p, double d);
        [DllImport("jpeg.dll", EntryPoint = "FreeFormattedString", CallingConvention = CallingConvention.Cdecl)]
        unsafe static extern void FreeFormattedString(IntPtr str);
        public String StringFormatDoubleG(int p, double d)
        {
            IntPtr ptr = FormatDoubleG(p, d);
            String str = System.Runtime.InteropServices.Marshal.PtrToStringAnsi(ptr);
            FreeFormattedString(ptr);
            return str;
        }
        public static string ToShortPathName(string longName)
        {
            uint bufferSize = 260;
            StringBuilder shortNameBuffer = new StringBuilder((int)bufferSize);
            uint result = GetShortPathName(longName, shortNameBuffer, bufferSize);
            return shortNameBuffer.ToString();
        }
        public ushort Find_POT(ushort x)
        {
            ushort i = 1;

            while (i < x)
            {
                i *= 2;
            }

            return i;
        }
        public void CopyToBuffer(Image src, Image dest, int x, int y)
        {
            var b = new Bitmap(src.Width + 2, src.Height + 2, src.PixelFormat);
            Graphics g = Graphics.FromImage(b);
            g.DrawImage(src, 1, 1, src.Width, src.Height);
            Graphics g2 = Graphics.FromImage(dest);
            g2.DrawImage(b, x, y, b.Width, b.Height);
        }
        public void Resize(string input, string output)
        {
            TGA intga = new TGA(input);
            ushort srcwidth = intga.Width;
            ushort srcheight = intga.Height;
            ushort destwidth = Find_POT((ushort)(intga.Width + 2));
            ushort destheight = Find_POT((ushort)(intga.Height + 2));
            int bpp = ((int)intga.Header.ImageSpec.PixelDepth) / 8;
            Bitmap src = intga.ToBitmap();
            Bitmap dest = new Bitmap(destwidth, destheight, src.PixelFormat);
            CopyToBuffer(src, dest, 0, 0);
            TGA outtga = TGA.FromBitmap(dest, false, false);
            outtga.Header.ColorMapSpec.ColorMapEntrySize = TgaColorMapEntrySize.A8R8G8B8;
            outtga.Save(output);
        }
        public void ResizeNoPack(int id, string input, string output, bool HasJpeg)
        {
            TGA intga = new TGA(input);
            NoPackedStrings.Add(@$"{id}=0 0 {intga.Width} {intga.Height}");

            if (HasJpeg)
            {
                NoPackedStrings.Add(@$"{id}=0 0 {intga.Width} {intga.Height}");
            }

            ushort srcwidth = intga.Width;
            ushort srcheight = intga.Height;
            ushort destwidth = Find_POT(srcwidth);
            ushort destheight = Find_POT(srcheight);
            int bpp = ((int)intga.Header.ImageSpec.PixelDepth) / 8;
            TgaImageType type = intga.Header.ImageType;

            if (GlobalData.IsRA3)
            {
                type = TgaImageType.Uncompressed_TrueColor;
            }

            TGA outtga = new TGA(destwidth, destheight, TgaPixelDepth.Bpp32, type, 8, false);
            outtga.Header.ColorMapSpec.ColorMapEntrySize = TgaColorMapEntrySize.A8R8G8B8;
            byte[] target = new byte[destwidth * destheight * 4];
            byte[] source = intga.ImageOrColorMapArea.ImageData;

            for (int i = 0; i < destheight; i++)
            {
                for (int j = 0; j < destwidth; j++)
                {
                    int x = i;

                    if (x >= srcheight)
                    {
                        x = srcheight - 1;
                    }

                    int y = j;

                    if (y >= srcwidth)
                    {
                        y = srcwidth - 1;
                    }

                    int src = ((srcheight - x - 1) * srcwidth * bpp) + (y * bpp);
                    int dest = ((destheight - i - 1) * destwidth * 4) + (j * 4);

                    for (int k = 0; k < bpp; k++)
                    {
                        target[dest + k] = source[src + k];

                        if (bpp != 4)
                        {
                            target[dest + 3] = 0xFF;
                        }
                    }
                }
            }

            outtga.ImageOrColorMapArea.ImageData = target;
            outtga.Save(output);
        }
        public void PackTextures(string basename)
        {
            foreach (var b in bitmaps)
            {
                if (b.NoPack)
                {
                    string name = b.TextureName;
                    string name2 = Path.ChangeExtension(b.TextureName, ".tga.noPack");
                    File.Move(name, name2);

                    if (b.HasJpeg)
                    {
                        string jname = b.JpegName;
                        string jname2 = Path.ChangeExtension(b.JpegName, ".jpg.noPack");
                        File.Move(jname, jname2);
                    }

                    string outname = @$"{GlobalData.artdir}\apt_{basename}_{b.ID}.tga";
                    ResizeNoPack(b.ID, name2, outname, b.HasJpeg);
                }
            }

            if (GlobalData.IsTT)
            {
                var process = Process.Start("ImagePacker", $@"-textureFormat A8R8G8B8 -R -XA -1024 -P apt_{basename} -O {GlobalData.artdir} -D {GlobalData.texturesdir}");
                process.WaitForExit();
            }
            else
            {
                var process = Process.Start("ImagePacker", $@"-textureFormat A8R8G8B8 -R -Z -1024 -P apt_{basename} -O {GlobalData.artdir} -D {GlobalData.texturesdir}");
                process.WaitForExit();
            }
        }
        void FindButtonHitTest()
        {
            for (int i = 0; i < GlobalData.AllCharacters.Length; i++)
            {
                if (GlobalData.AllCharacters[i] is AptCharacterButton button)
                {
                    foreach (var record in button.Tag.Characters)
                    {
                        if (record.StateDown || record.StateOver || record.StateUp)
                        {
                            GlobalData.ReferencedCharacters[record.CharacterID] = true;
                        }

                        if (record.StateHitTest)
                        {
                            GlobalData.HitTestShapes[record.CharacterID] = true;
                        }
                    }
                }
            }
        }
        double rXc(double[] row, double[] col)
        {
            return (row[0] * col[0]) + (row[1] * col[1]) + (row[2] * col[2]);
        }
        double[] MatMult(double[] m0, double[] m1)
        {
            double[] r0 = { m0[0], m0[1], 0 };
            double[] r1 = { m0[2], m0[3], 0 };
            double[] r2 = { m0[4], m0[5], 1 };

            double[] c0 = { m1[0], m1[2], m1[4] };
            double[] c1 = { m1[1], m1[3], m1[5] };
            double[] c2 = { 0, 0, 1 };

            double[] result = { rXc(r0,c0), rXc(r0,c1), rXc(r1,c0), rXc(r1,c1), rXc(r2,c0), rXc(r2,c1) };
            return result;
        }

        public void ConvertToApt(string filename, string basename, bool isra3, bool istt)
        {
            string aptname = Path.GetFileNameWithoutExtension(filename);
            string swfname = basename + "\\\\" + Path.GetFileName(filename);

            if (Directory.Exists(basename))
            {
                Directory.Delete(basename, true);
            }

            Directory.CreateDirectory(basename);
            basename += "\\";
            basename += aptname;
            File.Copy(filename, swfname);
            filename = ToShortPathName(swfname);

            if (Path.GetExtension(filename) != ".eaf")
            {
                string ra3 = "";

                if (isra3)
                {
                    ra3 = "--ra3";
                }

                string fname = filename;
                fname = Path.ChangeExtension(fname, null);
                string optname = fname + ".eaf";
                var process = Process.Start("flasm", @$"{filename} {optname} {ra3}");
                process.WaitForExit();
                int last = process.ExitCode;
                process = Process.Start("flasm", @$"{optname} {optname} {ra3}");
                process.WaitForExit();
                int current = process.ExitCode;

                while (last != current)
                {
                    last = current;
                    process = Process.Start("flasm", @$"{optname} {optname} {ra3}");
                    process.WaitForExit();
                    current = process.ExitCode;
                }

                filename = optname;
            }

            GlobalData = new Globals();
            GlobalData.writer = new ActionWriter(GlobalData);
            GlobalData.geometrydir = basename + "_geometry";
            GlobalData.texturesdir = basename + "_textures";
            GlobalData.soundsdir = basename + "_sounds";
            GlobalData.videodir = basename + "_videos";
            GlobalData.artdir = Directory.GetParent(basename) + "\\art\\textures";
            GlobalData.IsRA3 = isra3;
            GlobalData.IsTT = istt;

            if (Directory.Exists(GlobalData.geometrydir))
            {
                Directory.Delete(GlobalData.geometrydir, true);
            }

            if (Directory.Exists(GlobalData.texturesdir))
            {
                Directory.Delete(GlobalData.texturesdir, true);
            }

            if (Directory.Exists(GlobalData.soundsdir))
            {
                Directory.Delete(GlobalData.soundsdir, true);
            }

            if (Directory.Exists(GlobalData.videodir))
            {
                Directory.Delete(GlobalData.videodir, true);
            }

            if (Directory.Exists(Directory.GetParent(basename) + "\\art\\Textures"))
            {
                Directory.Delete(Directory.GetParent(basename) + "\\art\\Textures", true);
            }

            Directory.CreateDirectory(GlobalData.geometrydir);
            Directory.CreateDirectory(GlobalData.texturesdir);
            Directory.CreateDirectory(GlobalData.soundsdir);
            Directory.CreateDirectory(GlobalData.videodir);
            Directory.CreateDirectory(Directory.GetParent(basename) + "\\art\\Textures");

            using (var source = File.Open(filename, FileMode.Open, FileAccess.Read))
            {
                var swf = SwfFile.ReadFrom(source);
                List<SwfTagBase> CharacterList = new();
                List<ImportAssetsBase> ImportAssetsList = new();
                List<ExportAssetsTag> ExportAssetsList = new();
                List<DefineTextTag> DefineTextList = new();
                List<DefineText2Tag> DefineText2List = new();
                Dictionary<int, DefineFontInfoBaseTag> DefineFontInfoList = new();
                Dictionary<int, DefineFontBaseTag> FontBaseList = new();

                foreach (var item in swf.Tags)
                {
                    if (!item.IsControlTag)
                    {
                        CharacterList.Add(item);
                    }

                    switch (item)
                    {
                        case ImportAssetsBase import:
                            ImportAssetsList.Add(import);
                            break;
                        case ExportAssetsTag export:
                            ExportAssetsList.Add(export);
                            break;
                        case DefineTextTag definetext:
                            DefineTextList.Add(definetext);
                            break;
                        case DefineText2Tag definetext2:
                            DefineText2List.Add(definetext2);
                            break;
                        case DefineFontInfoBaseTag definefontinfo:
                            DefineFontInfoList.Add(item.TagID, definefontinfo);
                            break;
                        case DefineFontBaseTag definefont:
                            FontBaseList.Add(item.TagID, definefont);
                            break;
                    }
                }

                foreach (var item in CharacterList)
                {
                    var id = item.TagID;

                    if (id > GlobalData.LastID)
                    {
                        GlobalData.LastID = id;
                    }
                }

                GlobalData.LastID++;

                foreach (var import in ImportAssetsList)
                {
                    foreach (var i in import.Tags)
                    {
                        if (i >= GlobalData.LastID)
                        {
                            GlobalData.LastID++;
                        }
                    }
                }

                Array.Resize(ref GlobalData.Characters, GlobalData.LastID);

                foreach (var text in DefineTextList)
                {
                    foreach (var i in text.TextRecords)
                    {
                        if (i.FontID is not null)
                        {
                            FontBaseList[i.FontID.Value].UsedInStaticText = true;
                        }
                    }
                }

                foreach (var text in DefineText2List)
                {
                    foreach (var i in text.TextRecords)
                    {
                        if (i.FontID is not null)
                        {
                            FontBaseList[i.FontID.Value].UsedInStaticText = true;
                        }
                    }
                }

                foreach (var item in CharacterList)
                {
                    switch (item)
                    {
                        case DefineBitsLosslessTag definebitslossless:
                            GlobalData.Characters[item.TagID] = new AptCharacterBitmap(definebitslossless, GlobalData);
                            break;
                        case DefineBitsLossless2Tag definebitslossless2:
                            GlobalData.Characters[item.TagID] = new AptCharacterBitmap(definebitslossless2, GlobalData);
                            break;
                        case JPEGTablesTag tables:
                            GlobalData.JPEGTables = tables.JPEGData;
                            break;
                        case DefineBitsTag definebits:
                            GlobalData.Characters[item.TagID] = new AptCharacterBitmap(definebits, GlobalData);
                            break;
                        case DefineBitsJPEG2Tag definebitsjpeg2:
                            GlobalData.Characters[item.TagID] = new AptCharacterBitmap(definebitsjpeg2, GlobalData);
                            break;
                        case DefineBitsJPEG3Tag definebitsjpeg3:
                            GlobalData.Characters[item.TagID] = new AptCharacterBitmap(definebitsjpeg3, GlobalData);
                            break;
                        case DefineButton2Tag definebutton2:
                            GlobalData.Characters[item.TagID] = new AptCharacterButton(definebutton2, GlobalData);
                            break;
                        case DefineFontTag definefont:
                            if (DefineFontInfoList.TryGetValue(item.TagID, out var fontinfo))
                            {
                                GlobalData.Characters[item.TagID] = new AptCharacterFont(definefont, fontinfo, GlobalData);
                            }
                            break;
                        case DefineFont2BaseTag definefont2:
                            GlobalData.Characters[item.TagID] = new AptCharacterFont(definefont2, GlobalData);
                            break;
                        case DefineMorphShapeTag definemorphshape:
                            GlobalData.Characters[item.TagID] = new AptCharacterMorph(definemorphshape, GlobalData);
                            break;
                        case DefineShapeTag defineshape:
                            GlobalData.Characters[item.TagID] = new AptCharacterShape(defineshape, GlobalData);
                            break;
                        case DefineShape2Tag defineshape2:
                            GlobalData.Characters[item.TagID] = new AptCharacterShape(defineshape2, GlobalData);
                            break;
                        case DefineShape3Tag defineshape3:
                            GlobalData.Characters[item.TagID] = new AptCharacterShape(defineshape3, GlobalData);
                            break;
                        case DefineSoundTag definesound:
                            GlobalData.Characters[item.TagID] = new AptCharacterSound(definesound, GlobalData);
                            break;
                        case DefineSpriteTag definesprite:
                            GlobalData.Characters[item.TagID] = new AptCharacterSprite(definesprite, GlobalData);
                            break;
                        case DefineTextTag definetext:
                            GlobalData.Characters[item.TagID] = new AptCharacterStaticText(definetext, GlobalData);
                            break;
                        case DefineText2Tag definetext2:
                            GlobalData.Characters[item.TagID] = new AptCharacterStaticText(definetext2, GlobalData);
                            break;
                        case DefineEditTextTag defineedittext:
                            GlobalData.Characters[item.TagID] = new AptCharacterText(defineedittext, GlobalData);
                            break;
                        case DefineVideoStreamTag definevideostream:
                            GlobalData.Characters[item.TagID] = new AptCharacterVideo(definevideostream, GlobalData);
                            break;
                    }
                }

                GlobalData.AllCharacters = new AptCharacter[GlobalData.Characters.Length + GlobalData.ExtraCharacters.Count];

                for (int i = 0; i < GlobalData.Characters.Length; i++)
                {
                    GlobalData.AllCharacters[i] = GlobalData.Characters[i];
                }

                for (int i = 0; i < GlobalData.ExtraCharacters.Count; i++)
                {
                    GlobalData.AllCharacters[GlobalData.Characters.Length + i] = GlobalData.ExtraCharacters[i];
                }

                GlobalData.movie = new AptMovie(swf.Tags, GlobalData);
                List<AptExport> exports = new();

                foreach (var e in ExportAssetsList)
                {
                    foreach (var s in e.Symbols)
                    {
                        exports.Add(new(s.SymbolID, s.SymbolName));
                        GlobalData.ReferencedCharacters[s.SymbolID] = true;
                    }
                }

                List<AptImport> imports = new();

                foreach (var imp in ImportAssetsList)
                {
                    for (int i = 0; i < imp.Tags.Count; i++)
                    {
                        imports.Add(new(imp.URL, imp.Names[i], imp.Tags[i]));
                    }
                }

                FindButtonHitTest();
                AptCharacterAnimation a;

                using FileStream outfile = new FileStream(basename + ".apt", FileMode.Create);
                {
                    GlobalData.output.curpass = 0;

                    if (istt)
                    {
                        string tag = "Apt Data:1:" + (char)(swf.FileInfo.Version + 48) + ":4\u001A";
                        GlobalData.output.SetInitialValue(tag);
                    }
                    else
                    {
                        string tag = "Apt Data:" + (char)(swf.FileInfo.Version + 48) + "4\u001A\0";
                        GlobalData.output.SetInitialValue(tag);
                        GlobalData.output.Align(0);
                    }

                    int chars = GlobalData.AllCharacters.Length;

                    foreach (var i in imports)
                    {
                        if (i.ID > chars)
                        {
                            chars = i.ID + 1;
                        }
                    }

                    a = new AptCharacterAnimation(GlobalData.movie, GlobalData, 0, swf.Header.FrameRate, swf.Header.FrameSize, chars, imports, exports);
                    GlobalData.AllCharacters[0] = a;

                    for (int i = 0; i < chars; i++)
                    {
                        switch (GlobalData.AllCharacters[i])
                        {
                            case AptCharacterSprite sprite:
                                sprite.movie.AddConstants();
                                break;
                            case AptCharacterAnimation animation:
                                animation.movie.AddConstants();
                                break;
                            case AptCharacterBitmap bitmap:
                                bitmaps.Add(bitmap);
                                break;
                            case AptCharacterButton button:
                                foreach (var b in button.Tag.Conditions)
                                {
                                    GlobalData.writer.AddActionConstants(b.Actions);
                                }
                                button.UpdateHitTestShape();
                                break;
                            case AptCharacterShape shape:
                                shape.UpdateShape(i);
                                shapes.Add(shape);
                                break;
                        }
                    }

                    a.WriteImportsExports();
                    GlobalData.MaxPasses = 5;

                    for (GlobalData.output.curpass = 1; GlobalData.output.curpass <= GlobalData.MaxPasses; GlobalData.output.curpass++)
                    {
                        GlobalData.output.Align(1);

                        if (GlobalData.output.curpass == 1)
                        {
                            a.constpointers[ConstPointerType.characters] = GlobalData.output.GetSize();
                        }

                        if (GlobalData.output.curpass == 3)
                        {
                            a.constpointers[ConstPointerType.maincharacter] = GlobalData.output.GetSize();
                        }

                        for (int i = 0; i < chars; i++)
                        {
                            var ch = GlobalData.AllCharacters[i];

                            if (ch is null)
                            {
                                GlobalData.output.Write(2, 0);
                                continue;
                            }

                            ch.OutputCharacter(i);
                        }
                    }

                    outfile.Write(GlobalData.output.GetBuffer());
                    GlobalData.output.curpass = 0;
                }
                using FileStream outfile2 = new FileStream(basename + ".const", FileMode.Create);
                {
                    GlobalData.output.SetInitialValue("Apt constant file\u001A\0");
                    GlobalData.MaxPasses = 1;

                    for (GlobalData.output.curpass = 1; GlobalData.output.curpass <= GlobalData.MaxPasses; GlobalData.output.curpass++)
                    {
                        GlobalData.output.Write(1, a.constpointers[ConstPointerType.maincharacter]);
                    }

                    GlobalData.writer.WriteConstTable();
                    outfile2.Write(GlobalData.output.GetBuffer());
                }

                PackTextures(aptname);

                foreach (var s in shapes)
                {
                    ShapeIDs.Add(s.outid.ToString());
                    s.WriteShapeFile();
                }

                string INI = @$"{GlobalData.artdir}\apt_{aptname}.ini";
                IntPtr table = GetCharHashTable();

                using FileStream INIFile = new FileStream(INI, FileMode.Open);
                {
                    using StreamReader sr = new StreamReader(INIFile);
                    {
                        int current = 0;

                        while (!sr.EndOfStream)
                        {
                            string line = sr.ReadLine();

                            if (Regex.IsMatch(line, @$"^\s*;"))
                            {
                                continue;
                            }

                            Match m = Regex.Match(line, @$"^\s*MappedImage (\d*)");

                            if (m.Success && m.Groups.Count >= 2)
                            {
                                current = Convert.ToInt32(m.Groups[1].Value);
                                textures.Add(current, new TextureEntry());
                                continue;
                            }

                            m = Regex.Match(line, @$"^\s*Texture\s*=\s*apt_{aptname}_(\d*)");

                            if (m.Success && m.Groups.Count >= 2)
                            {
                                textures[current].MapsTo = Convert.ToInt32(m.Groups[1].Value);
                                if (GlobalData.IsTT)
                                {
                                    StoreCharEntry(table, current.ToString(), @$"{current}->{textures[current].MapsTo.ToString("D3")}");
                                }
                                else
                                {
                                    StoreCharEntry(table, current.ToString(), @$"{current}->{textures[current].MapsTo}");
                                }
                                continue;
                            }

                            m = Regex.Match(line, @$"^\s*Coords\s*=\s*Left:(\d*)\s*Top:(\d*)\s*Right:(\d*)\s*Bottom:(\d*)");

                            if (m.Success && m.Groups.Count >= 5)
                            {
                                textures[current].OffsetX = Convert.ToInt32(m.Groups[1].Value);
                                textures[current].OffsetY = Convert.ToInt32(m.Groups[2].Value);
                                textures[current].OrigWidth = Convert.ToInt32(m.Groups[3].Value) - Convert.ToInt32(m.Groups[1].Value);
                                textures[current].OrigHeight = Convert.ToInt32(m.Groups[4].Value) - Convert.ToInt32(m.Groups[2].Value);
                                continue;
                            }

                            m = Regex.Match(line, @$"^\s*TextureWidth\s*=\s*(\d*)");

                            if (m.Success && m.Groups.Count >= 2)
                            {
                                textures[current].Width = Convert.ToInt32(m.Groups[1].Value);
                                continue;
                            }

                            m = Regex.Match(line, @$"^\s*TextureHeight\s*=\s*(\d*)");

                            if (m.Success && m.Groups.Count >= 2)
                            {
                                textures[current].Height = Convert.ToInt32(m.Groups[1].Value);
                                continue;
                            }

                            if (Regex.IsMatch(line, @$"Status\s*="))
                            {
                                textures[current].rotated = Regex.IsMatch(line, @$"ROTATED_90_CLOCKWISE");
                                continue;
                            }
                        }
                    }
                }

                table = CopyCharHashTable(table);
                NoPackedStrings.Sort();

                using FileStream outfile3 = new FileStream(basename + ".dat", FileMode.Create);
                {
                    using StreamWriter sr = new StreamWriter(outfile3);
                    {
                        sr.WriteLine("; Created by AptToXML.");

                        foreach (var s in NoPackedStrings)
                        {
                            sr.WriteLine(s);
                        }

                        sr.WriteLine("; Created by AptToXML.");
                        int count = ResetCharIterator(table);

                        for (int i = 0; i < count; i++)
                        {
                            String s = System.Runtime.InteropServices.Marshal.PtrToStringAnsi(GetCharValue(table));
                            sr.WriteLine(s);
                        }
                    }
                }

                FreeCharHashTable(table);
                var geometryfiles = Directory.EnumerateFiles(GlobalData.geometrydir, "*.ru");

                foreach (string file in geometryfiles)
                {
                    StringWriter newstring = new();

                    int changes = 0;
                    {
                        using FileStream rufile = new FileStream(file, FileMode.Open);
                        {
                            using StreamReader sr = new StreamReader(rufile);
                            {
                                while (!sr.EndOfStream)
                                {
                                    string line = sr.ReadLine();
                                    Match m = Regex.Match(line, @$"^(s t[cw]:\d+:\d+:\d+:\d+:)(\d+):(.+)$");

                                    if (m.Success && m.Groups.Count >= 4)
                                    {
                                        string front = m.Groups[1].Value;
                                        int id = Convert.ToInt32(m.Groups[2].Value);
                                        string[] str = m.Groups[3].Value.Split(':');
                                        double[] matrix = new double[str.Length];

                                        for (int i = 0; i < str.Length; i++)
                                        {
                                            matrix[i] = Convert.ToDouble(str[i]);
                                        }

                                        if (textures.ContainsKey(id))
                                        {
                                            if (textures[id].rotated)
                                            {
                                                double t = matrix[0];
                                                matrix[0] = matrix[1];
                                                matrix[1] = t;

                                                t = matrix[2];
                                                matrix[2] = -matrix[3];
                                                matrix[3] = -t;

                                                t = matrix[4];
                                                matrix[4] = matrix[5];
                                                matrix[5] = -t;
                                            }

                                            double[] offset = { 1, 0, 0, 1, textures[id].OffsetX, textures[id].OffsetY };
                                            matrix = MatMult(matrix, offset);
                                            line = front + id + ':' + @$"{StringFormatDoubleG(15, matrix[0])}:{StringFormatDoubleG(15, matrix[1])}:{StringFormatDoubleG(15, matrix[2])}:{StringFormatDoubleG(15, matrix[3])}:{StringFormatDoubleG(15, matrix[4])}:{StringFormatDoubleG(15, matrix[5])}";
                                            changes++;
                                        }
                                    }

                                    newstring.WriteLine(line);
                                }
                            }
                        }
                    }

                    if (changes != 0)
                    {
                        File.Move(file, file + ".o");

                        using FileStream rufile = new FileStream(file, FileMode.Create);
                        {
                            using StreamWriter sr = new StreamWriter(rufile);
                            {
                                sr.Write(newstring.ToString());
                            }
                        }
                    }
                }

                using FileStream outfile4 = new FileStream(basename + ".xml", FileMode.Create);
                {
                    using StreamWriter sr = new StreamWriter(outfile4);
                    string format = "A8R8G8B8";
                    sr.WriteLine("<?xml version='1.0' encoding='utf-8'?>");
                    sr.WriteLine("<AssetDeclaration xmlns=\"uri:ea.com:eala:asset\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\">");
                    sr.WriteLine("\t<AptAptData id=\"{0}_apt\" File=\"{1}.apt\" />", aptname, aptname);
                    sr.WriteLine("\t<AptConstData id=\"{0}_const\" File=\"{1}.const\" />", aptname, aptname);
                    sr.WriteLine("\t<AptDatData id=\"{0}_dat\" File=\"{1}.dat\" />", aptname, aptname);

                    foreach (var geometryfile in geometryfiles)
                    {
                        int id = Convert.ToInt32(Path.GetFileNameWithoutExtension(geometryfile));
                        sr.WriteLine("\t<AptGeometryData id=\"{0}_{1}\" File=\"{2}_geometry\\{3}.ru\" AptID=\"{4}\"/>", aptname, id, aptname, id, id);
                    }

                    var texturefiles = Directory.EnumerateFiles(GlobalData.artdir, "*.tga");

                    foreach (var texturefile in texturefiles)
                    {
                        sr.WriteLine("\t<Texture id=\"{0}\" File=\"{1}\\{2}\" OutputFormat=\"{3}\" GenerateMipMaps=\"false\" AllowAutomaticResize=\"false\"/>", Path.GetFileNameWithoutExtension(texturefile), "art\\Textures", Path.GetFileName(texturefile), format);
                    }

                    sr.WriteLine("</AssetDeclaration>");
                }
            }
        }
    }
}
