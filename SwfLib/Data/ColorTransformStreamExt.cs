using SwfLib.Utils;

namespace SwfLib.Data {
    public static class ColorTransformStreamExt {

        public static ColorTransformRGB ReadColorTransformRGB(this ISwfStreamReader reader) {
            ColorTransformRGB transform;
            var hasAddTerms = reader.ReadBit();
            var hasMultTerms = reader.ReadBit();
            var bits = reader.ReadUnsignedBits(4);
            if (hasMultTerms) {
                transform.RedMultTerm = (short)reader.ReadSignedBits(bits);
                transform.GreenMultTerm = (short)reader.ReadSignedBits(bits);
                transform.BlueMultTerm = (short)reader.ReadSignedBits(bits);
                transform.HasMultTerms = true;
            } else {
                transform.RedMultTerm = 255;
                transform.GreenMultTerm = 255;
                transform.BlueMultTerm = 255;
                transform.HasMultTerms = false;
            }
            if (hasAddTerms) {
                transform.RedAddTerm = (short)reader.ReadSignedBits(bits);
                transform.GreenAddTerm = (short)reader.ReadSignedBits(bits);
                transform.BlueAddTerm = (short)reader.ReadSignedBits(bits);
                transform.HasAddTerms = true;
            } else {
                transform.RedAddTerm = 0;
                transform.GreenAddTerm = 0;
                transform.BlueAddTerm = 0;
                transform.HasAddTerms = false;
            }
            reader.AlignToByte();
            return transform;
        }

        public static ColorTransformRGBA ReadColorTransformRGBA(this ISwfStreamReader reader) {
            ColorTransformRGBA transform;
            reader.ReadColorTransformRGBA(out transform);
            return transform;
        }

        public static void ReadColorTransformRGBA(this ISwfStreamReader reader, out ColorTransformRGBA transform) {
            var hasAddTerms = reader.ReadBit();
            var hasMultTerms = reader.ReadBit();
            var bits = reader.ReadUnsignedBits(4);
            if (hasMultTerms) {
                transform.RedMultTerm = (short)reader.ReadSignedBits(bits);
                transform.GreenMultTerm = (short)reader.ReadSignedBits(bits);
                transform.BlueMultTerm = (short)reader.ReadSignedBits(bits);
                transform.AlphaMultTerm = (short)reader.ReadSignedBits(bits);
                transform.HasMultTerms = true;
            } else {
                transform.RedMultTerm = 255;
                transform.GreenMultTerm = 255;
                transform.BlueMultTerm = 255;
                transform.AlphaMultTerm = 255;
                transform.HasMultTerms = false;
            }
            if (hasAddTerms) {
                transform.RedAddTerm = (short)reader.ReadSignedBits(bits);
                transform.GreenAddTerm = (short)reader.ReadSignedBits(bits);
                transform.BlueAddTerm = (short)reader.ReadSignedBits(bits);
                transform.AlphaAddTerm = (short)reader.ReadSignedBits(bits);
                transform.HasAddTerms = true;
            } else {
                transform.RedAddTerm = 0;
                transform.GreenAddTerm = 0;
                transform.BlueAddTerm = 0;
                transform.AlphaAddTerm = 0;
                transform.HasAddTerms = false;
            }
            reader.AlignToByte();
        }
    }
}
