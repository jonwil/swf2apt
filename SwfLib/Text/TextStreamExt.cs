using System;
using System.Collections.Generic;
using SwfLib.Data;

namespace SwfLib.Text {
    /// <summary>
    /// Represents stream extensions for reading and writing text structures.
    /// </summary>
    public static class TextStreamExt {

        public static List<TextRecordRGB> ReadTextRecordsRGB(this ISwfStreamReader reader, uint glyphBits, uint advanceBits) {
            var res = new List<TextRecordRGB>();
            bool isEnd;
            do {
                var record = new TextRecordRGB();
                record.Type = reader.ReadBit();
                record.Reserved = (byte)reader.ReadUnsignedBits(3);
                var hasFont = reader.ReadBit();
                var hasColor = reader.ReadBit();
                var hasYOffset = reader.ReadBit();
                var hasXOffset = reader.ReadBit();

                isEnd = !record.Type && record.Reserved == 0 && !hasFont && !hasColor && !hasYOffset && !hasXOffset;

                if (!isEnd) {
                    record.FontID = hasFont ? (ushort?)reader.ReadUInt16() : null;
                    if (hasColor) {
                        record.TextColor = reader.ReadRGB();
                    }
                    if (hasXOffset) {
                        record.XOffset = reader.ReadSInt16();
                    }
                    if (hasYOffset) {
                        record.YOffset = reader.ReadSInt16();
                    }
                    if (hasFont) {
                        record.TextHeight = reader.ReadUInt16();
                    }
                    var count = reader.ReadByte();
                    for (var i = 0; i < count; i++) {
                        var entry = reader.ReadGlyphEntry(glyphBits, advanceBits);
                        record.Glyphs.Add(entry);
                    }
                    reader.AlignToByte();
                }
                if (!isEnd)
                {
                    res.Add(record);
                }
            } while (!isEnd);
            return res;
        }

        public static List<TextRecordRGBA> ReadTextRecordsRGBA(this ISwfStreamReader reader, uint glyphBits, uint advanceBits) {
            var res = new List<TextRecordRGBA>();
            bool isEnd;
            do {
                var record = new TextRecordRGBA();
                record.Type = reader.ReadBit();
                record.Reserved = (byte)reader.ReadUnsignedBits(3);
                var hasFont = reader.ReadBit();
                var hasColor = reader.ReadBit();
                var hasYOffset = reader.ReadBit();
                var hasXOffset = reader.ReadBit();

                isEnd = !record.Type && record.Reserved == 0 && !hasFont && !hasColor && !hasYOffset && !hasXOffset;

                if (!isEnd) {
                    record.FontID = hasFont ? (ushort?)reader.ReadUInt16() : null;
                    if (hasColor) {
                        record.TextColor = reader.ReadRGBA();
                    }
                    if (hasXOffset) {
                        record.XOffset = reader.ReadSInt16();
                    }
                    if (hasYOffset) {
                        record.YOffset = reader.ReadSInt16();
                    }
                    if (hasFont) {
                        record.TextHeight = reader.ReadUInt16();
                    }
                    var count = reader.ReadByte();
                    for (var i = 0; i < count; i++) {
                        var entry = reader.ReadGlyphEntry(glyphBits, advanceBits);
                        record.Glyphs.Add(entry);
                    }
                    reader.AlignToByte();
                }
                res.Add(record);
            } while (!isEnd);
            return res;
        }

        /// <summary>
        /// Reads GlyphEntry from reader.
        /// </summary>
        /// <param name="reader">Reader from which to read GlyphEntry.</param>
        /// <param name="glyphBits">Bits count used for reading glyph index.</param>
        /// <param name="advanceBits">Bits count used for reading advance value.</param>
        /// <returns></returns>
        public static GlyphEntry ReadGlyphEntry(this ISwfStreamReader reader, uint glyphBits, uint advanceBits) {
            var entry = new GlyphEntry {
                GlyphIndex = reader.ReadUnsignedBits(glyphBits),
                GlyphAdvance = reader.ReadSignedBits(advanceBits)
            };
            return entry;
        }
    }
}
