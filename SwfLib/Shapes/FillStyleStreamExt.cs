using System;
using System.Collections.Generic;
using SwfLib.Shapes.FillStyles;

namespace SwfLib.Shapes {
    public static class FillStyleStreamExt {

        private static readonly FillStyleRGBReader _readerRGB = new FillStyleRGBReader();
        private static readonly FillStyleRGBAReader _readerRGBA = new FillStyleRGBAReader();
        public static void ReadToFillStylesRGB(this ISwfStreamReader reader, List<FillStyleRGB> fillStyles, bool allowBigArray) {
            ushort count = reader.ReadByte();
            if (allowBigArray && count == 255) {
                count = reader.ReadUInt16();
            }
            for (var i = 0; i < count; i++) {
                FillStyleRGB style = reader.ReadFillStyleRGB();
                fillStyles.Add(style);
            }
        }

        public static void ReadToFillStylesRGBA(this ISwfStreamReader reader, List<FillStyleRGBA> fillStyles) {
            ushort count = reader.ReadByte();
            if (count == 255) {
                count = reader.ReadUInt16();
            }
            for (var i = 0; i < count; i++) {
                FillStyleRGBA style = reader.ReadFillStyleRGBA();
                fillStyles.Add(style);
            }
        }
        public static void ReadToMorphFillStylesRGBA(this ISwfStreamReader reader, List<FillStyleRGBA> startFillStyles, List<FillStyleRGBA> endFillStyles)
        {
            ushort count = reader.ReadByte();
            if (count == 255)
            {
                count = reader.ReadUInt16();
            }
            for (var i = 0; i < count; i++)
            {
                FillStyleRGBA style = reader.ReadMorphFillStyleRGBA();
                switch (style)
                {
                    case SolidMorphFillStyleRGBA:
                        {
                            var s = style as SolidMorphFillStyleRGBA;
                            var s1 = new SolidFillStyleRGBA();
                            var s2 = new SolidFillStyleRGBA();
                            s1.Color = s.StartColor;
                            s2.Color = s.EndColor;
                            startFillStyles.Add(s1);
                            endFillStyles.Add(s2);
                        }
                        break;
                    case BitmapMorphFillStyleRGBA:
                        {
                            var s = style as BitmapMorphFillStyleRGBA;
                            var s1 = new BitmapFillStyleRGBA();
                            var s2 = new BitmapFillStyleRGBA();
                            s1.BitmapID = s.BitmapID;
                            s2.BitmapID = s.BitmapID;
                            s1.BitmapMatrix = s.StartBitmapMatrix;
                            s2.BitmapMatrix = s.EndBitmapMatrix;
                            s1.Mode = s.Mode;
                            s2.Mode = s.Mode;
                            s1.Smoothing = s.Smoothing;
                            s2.Smoothing = s.Smoothing;
                            startFillStyles.Add(s1);
                            endFillStyles.Add(s2);
                        }
                        break;
                }
            }
        }

        public static FillStyleRGB ReadFillStyleRGB(this ISwfStreamReader reader) {
            var type = (FillStyleType)reader.ReadByte();
            return _readerRGB.Read(reader, type);
        }

        public static FillStyleRGBA ReadFillStyleRGBA(this ISwfStreamReader reader) {
            var type = (FillStyleType)reader.ReadByte();
            return _readerRGBA.Read(reader, type);
        }

        public static FillStyleRGBA ReadMorphFillStyleRGBA(this ISwfStreamReader reader)
        {
            var type = (FillStyleType)reader.ReadByte();
            return _readerRGBA.ReadMorph(reader, type);
        }
    }
}
