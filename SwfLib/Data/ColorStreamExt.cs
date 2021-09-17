namespace SwfLib.Data {
    /// <summary>
    /// Represents extensions to ISwfStreamReader for reading color records.
    /// </summary>
    public static class ColorStreamExt {
        
        public static SwfRGB ReadRGB(this ISwfStreamReader reader) {
            SwfRGB color;
            reader.ReadRGB(out color);
            return color;
        }

        public static void ReadRGB(this ISwfStreamReader reader, out SwfRGB color) {
            color.Red = reader.ReadByte();
            color.Green = reader.ReadByte();
            color.Blue = reader.ReadByte();
        }

        public static SwfRGBA ReadRGBA(this ISwfStreamReader reader) {
            return new SwfRGBA {
                Red = reader.ReadByte(),
                Green = reader.ReadByte(),
                Blue = reader.ReadByte(),
                Alpha = reader.ReadByte()
            };
        }

        public static SwfRGBA ReadARGB(this ISwfStreamReader reader) {
            var rgb = new SwfRGBA {
                Alpha = reader.ReadByte(),
                Red = reader.ReadByte(),
                Green = reader.ReadByte(),
                Blue = reader.ReadByte()
            };
            return rgb;
        }
    }
}
