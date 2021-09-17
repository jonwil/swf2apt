using System;
using SwfLib.Data;

namespace SwfLib.Gradients {
    public static class GradientStreamExt {

        #region Linear Gradient

        /// <summary>
        /// Reads RGB gradient from the reader.
        /// </summary>
        /// <param name="reader">The reader from which to read gradient.</param>
        /// <returns></returns>
        public static GradientRGB ReadGradientRGB(this ISwfStreamReader reader) {
            var gradient = new GradientRGB {
                SpreadMode = (SpreadMode)reader.ReadUnsignedBits(2),
                InterpolationMode = (InterpolationMode)reader.ReadUnsignedBits(2)
            };
            var count = reader.ReadUnsignedBits(4);
            for (var i = 0; i < count; i++) {
                GradientRecordRGB record = reader.ReadGradientRecordRGB();
                gradient.GradientRecords.Add(record);
            }
            return gradient;
        }

        /// <summary>
        /// Reads RGBA gradient from the reader.
        /// </summary>
        /// <param name="reader">The reader from which to read gradient.</param>
        /// <returns></returns>
        public static GradientRGBA ReadGradientRGBA(this ISwfStreamReader reader) {
            var gradient = new GradientRGBA {
                SpreadMode = (SpreadMode)reader.ReadUnsignedBits(2),
                InterpolationMode = (InterpolationMode)reader.ReadUnsignedBits(2)
            };
            var count = reader.ReadUnsignedBits(4);
            for (var i = 0; i < count; i++) {
                GradientRecordRGBA record = reader.ReadGradientRecordRGBA();
                gradient.GradientRecords.Add(record);
            }
            return gradient;
        }

        #endregion

        #region Gradient records

        public static GradientRecordRGB ReadGradientRecordRGB(this ISwfStreamReader reader) {
            var record = new GradientRecordRGB {
                Ratio = reader.ReadByte(),
                Color = reader.ReadRGB()
            };
            return record;
        }

        public static GradientRecordRGBA ReadGradientRecordRGBA(this ISwfStreamReader reader) {
            var record = new GradientRecordRGBA {
                Ratio = reader.ReadByte(),
                Color = reader.ReadRGBA()
            };
            return record;
        }

        #endregion

    }
}
