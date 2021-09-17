using System;
using System.Collections.Generic;
using SwfLib.Data;
using SwfLib.Shapes.LineStyles;

namespace SwfLib.Shapes {
    public static class LineStyleStreamExt {

        public static void ReadToLineStylesRGB(this ISwfStreamReader reader, List<LineStyleRGB> lineStyles, bool allowBigArray) {
            ushort cnt = reader.ReadByte();
            if (allowBigArray && cnt == 255) {
                cnt = reader.ReadUInt16();
            }
            for (var i = 0; i < cnt; i++) {
                lineStyles.Add(reader.ReadLineStyleRGB());
            }
        }

        public static void ReadToLineStylesRGBA(this ISwfStreamReader reader, List<LineStyleRGBA> lineStyles) {
            ushort cnt = reader.ReadByte();
            if (cnt == 255) {
                cnt = reader.ReadUInt16();
            }
            for (var i = 0; i < cnt; i++) {
                lineStyles.Add(reader.ReadLineStyleRGBA());
            }
        }
        public static void ReadToMorphLineStylesRGBA(this ISwfStreamReader reader, List<LineStyleRGBA> startLineStyles, List<LineStyleRGBA> endLineStyles)
        {
            ushort cnt = reader.ReadByte();
            if (cnt == 255)
            {
                cnt = reader.ReadUInt16();
            }
            for (var i = 0; i < cnt; i++)
            {
                var s = reader.ReadMorphLineStyleRGBA();
                var s1 = new LineStyleRGBA();
                var s2 = new LineStyleRGBA();
                s1.Color = s.StartColor;
                s2.Color = s.EndColor;
                s1.Width = s.StartWidth;
                s2.Width = s.EndWidth;
                startLineStyles.Add(s1);
                endLineStyles.Add(s2);
            }
        }

        public static void ReadToLineStylesEx(this ISwfStreamReader reader, List<LineStyleEx> lineStyles) {
            ushort cnt = reader.ReadByte();
            if (cnt == 255) {
                cnt = reader.ReadUInt16();
            }
            for (var i = 0; i < cnt; i++) {
                lineStyles.Add(reader.ReadLineStyleEx());
            }
        }
        public static LineStyleRGB ReadLineStyleRGB(this ISwfStreamReader reader) {
            var lineStyle = new LineStyleRGB {
                Width = reader.ReadUInt16(),
                Color = reader.ReadRGB()
            };
            return lineStyle;
        }

        public static LineStyleRGBA ReadLineStyleRGBA(this ISwfStreamReader reader) {
            var lineStyle = new LineStyleRGBA {
                Width = reader.ReadUInt16(),
                Color = reader.ReadRGBA()
            };
            return lineStyle;
        }

        public static MorphLineStyleRGBA ReadMorphLineStyleRGBA(this ISwfStreamReader reader)
        {
            var lineStyle = new MorphLineStyleRGBA
            {
                StartWidth = reader.ReadUInt16(),
                EndWidth = reader.ReadUInt16(),
                StartColor = reader.ReadRGBA(),
                EndColor = reader.ReadRGBA()
            };
            return lineStyle;
        }

        public static LineStyleEx ReadLineStyleEx(this ISwfStreamReader reader) {
            var lineStyle = new LineStyleEx {
                Width = reader.ReadUInt16(),
                StartCapStyle = (CapStyle)reader.ReadUnsignedBits(2),
                JoinStyle = (JoinStyle)reader.ReadUnsignedBits(2),
                HasFill = reader.ReadBit(),
                NoHScale = reader.ReadBit(),
                NoVScale = reader.ReadBit(),
                PixelHinting = reader.ReadBit(),
                Reserved = (byte)reader.ReadUnsignedBits(5),
                NoClose = reader.ReadBit(),
                EndCapStyle = (CapStyle)reader.ReadUnsignedBits(2)
            };
            if (lineStyle.JoinStyle == JoinStyle.Miter) {
                lineStyle.MilterLimitFactor = reader.ReadFixedPoint8();
            }
            if (lineStyle.HasFill) {
                lineStyle.FillStyle = reader.ReadFillStyleRGBA();
            } else {
                lineStyle.Color = reader.ReadRGBA();
            }
            return lineStyle;
        }
    }
}
