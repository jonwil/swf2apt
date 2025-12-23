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

using System.Collections.Generic;
using System.IO;
using SwfLib.Data;

namespace eaf2apt
{
    class AptOutput
    {
        public int curpass = 0;
        MemoryStream stream;
        BinaryWriter sr;
        Dictionary<string, int> fixups = new();
        public void Align(int pass)
        {
            if (curpass != pass)
            {
                return;
            }

            while (stream.Length % 4 != 0)
            {
                byte b = 0;
                sr.Write(b);
            }
        }
        public void Write(int pass, string str)
        {
            if (curpass != pass)
            {
                return;
            }

            if (str is not null)
            {
                sr.Write(str.ToCharArray());
            }

            sr.Write((byte)0);
        }
        public void Write(int pass, uint value)
        {
            if (curpass != pass)
            {
                return;
            }

            sr.Write(value);
        }
        public void Write(int pass, int value)
        {
            if (curpass != pass)
            {
                return;
            }

            sr.Write(value);
        }
        public void Write(int pass, bool value)
        {
            if (curpass != pass)
            {
                return;
            }

            int i;

            if (value)
            {
                i = 1;
            }
            else
            {
                i = 0;
            }

            sr.Write(i);
        }
        public void Write(int pass, ushort value)
        {
            if (curpass != pass)
            {
                return;
            }

            sr.Write(value);
        }
        public void Write(int pass, byte value)
        {
            if (curpass != pass)
            {
                return;
            }

            sr.Write(value);
        }
        public void WriteFixup(int pass, string fixup)
        {
            if (curpass != pass)
            {
                return;
            }

            fixups[fixup] = (int)stream.Length;
            int i = 0;
            sr.Write(i);
        }
        public void FixupPointer(int pass, string fixup)
        {
            if (curpass != pass)
            {
                return;
            }

            int length = (int)stream.Length;
            int address = length;
            sr.Seek(fixups[fixup], SeekOrigin.Begin);
            sr.Write(address);
            sr.Seek(0, SeekOrigin.End);
            fixups.Remove(fixup);
        }
        public void FixupInt(int pass, string fixup, int value)
        {
            if (curpass != pass)
            {
                return;
            }

            sr.Seek(fixups[fixup], SeekOrigin.Begin);
            sr.Write(value);
            sr.Seek(0, SeekOrigin.End);
            fixups.Remove(fixup);
        }
        public void SetInitialValue(string value)
        {
            stream = new();
            sr = new(stream);
            sr.Write(value.ToCharArray());
            sr.Write((byte)0);
        }
        public void Write(int pass, float value)
        {
            if (curpass != pass)
            {
                return;
            }

            sr.Write(value);
        }
        unsafe public void Write(int pass, AptRect boundingrect)
        {
            if (curpass != pass)
            {
                return;
            }

            Write(pass, boundingrect.fLeft);
            Write(pass, boundingrect.fTop);
            Write(pass, boundingrect.fRight);
            Write(pass, boundingrect.fBottom);
        }
        public void Write(int pass, SwfMatrix matrix)
        {
            if (curpass != pass)
            {
                return;
            }

            sr.Write((float)matrix.ScaleX);
            sr.Write((float)matrix.RotateSkew0);
            sr.Write((float)matrix.RotateSkew1);
            sr.Write((float)matrix.ScaleY);
            sr.Write(matrix.TranslateX / 20.0f);
            sr.Write(matrix.TranslateY / 20.0f);
        }
        byte ToColor(short color)
        {
            return (byte)((color / 256.0f) * 255.0f);
        }
        public void Write(int pass, ColorTransformRGBA color, bool enable)
        {
            if (curpass != pass)
            {
                return;
            }

            if (enable && color.HasMultTerms)
            {
                Write(pass, ToColor(color.BlueMultTerm));
                Write(pass, ToColor(color.GreenMultTerm));
                Write(pass, ToColor(color.RedMultTerm));
                Write(pass, ToColor(color.AlphaMultTerm));
            }
            else
            {
                Write(pass, (byte)255);
                Write(pass, (byte)255);
                Write(pass, (byte)255);
                Write(pass, (byte)255);
            }

            if (enable && color.HasAddTerms)
            {
                Write(pass, ToColor(color.BlueAddTerm));
                Write(pass, ToColor(color.GreenAddTerm));
                Write(pass, ToColor(color.RedAddTerm));
                Write(pass, ToColor(color.AlphaAddTerm));
            }
            else
            {
                Write(pass, (byte)0);
                Write(pass, (byte)0);
                Write(pass, (byte)0);
                Write(pass, (byte)0);
            }
        }
        public void Write(int pass, ColorTransformRGBA color)
        {
            if (curpass != pass)
            {
                return;
            }

            if (color.HasMultTerms)
            {
                Write(pass, color.RedMultTerm / 256.0f);
                Write(pass, color.GreenMultTerm / 256.0f);
                Write(pass, color.BlueMultTerm / 256.0f);
                Write(pass, color.AlphaMultTerm / 256.0f);
            }
            else
            {
                Write(pass, 1.0f);
                Write(pass, 1.0f);
                Write(pass, 1.0f);
                Write(pass, 1.0f);
            }

            if (color.HasAddTerms)
            {
                Write(pass, color.RedAddTerm / 256.0f);
                Write(pass, color.GreenAddTerm / 256.0f);
                Write(pass, color.BlueAddTerm / 256.0f);
                Write(pass, color.AlphaAddTerm / 256.0f);
            }
            else
            {
                Write(pass, 0.0f);
                Write(pass, 0.0f);
                Write(pass, 0.0f);
                Write(pass, 0.0f);
            }
        }
        unsafe public void Write(int pass, AptFloatArrayCXForm color)
        {
            if (curpass != pass)
            {
                return;
            }

            Write(pass, color.scale[0] / 256.0f);
            Write(pass, color.scale[1] / 256.0f);
            Write(pass, color.scale[2] / 256.0f);
            Write(pass, color.scale[3] / 256.0f);
            Write(pass, color.translate[0] / 256.0f);
            Write(pass, color.translate[1] / 256.0f);
            Write(pass, color.translate[2] / 256.0f);
            Write(pass, color.translate[3] / 256.0f);
        }
        public void Write(int pass, SwfRGB color)
        {
            if (curpass != pass)
            {
                return;
            }

            int c = (255 << 24) | (color.Red << 16) | (color.Green << 8) | (color.Blue);
            sr.Write(c);
        }
        public void Write(int pass, SwfRGBA color)
        {
            if (curpass != pass)
            {
                return;
            }

            int c = (color.Alpha << 24) | (color.Red << 16) | (color.Green << 8) | (color.Blue);
            sr.Write(c);
        }
        public int GetSize()
        {
            return (int)stream.Length;
        }
        public byte[] GetBuffer()
        {
            return stream.ToArray();
        }
    }
}
