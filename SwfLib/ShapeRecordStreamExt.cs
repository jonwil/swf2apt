using System.Collections.Generic;
using SwfLib.Shapes;
using SwfLib.Shapes.Records;

namespace SwfLib {
    public static class ShapeRecordStreamExt {

        private static ShapeRecordRGBReader _shapeRecordRGBReader = new ShapeRecordRGBReader();
        private static ShapeRecordRGBAReader _shapeRecordRGBAReader = new ShapeRecordRGBAReader();
        private static ShapeRecordExReader _shapeRecorExReader = new ShapeRecordExReader();

        public static void ReadToShapeRecordsRGB(this ISwfStreamReader reader, List<IShapeRecordRGB> shapeRecords) {
            var fillStyleBits = reader.ReadUnsignedBits(4);
            var lineStyleBits = reader.ReadUnsignedBits(4);
            reader.AlignToByte();
            IShapeRecordRGB record;
            do {
                record = _shapeRecordRGBReader.Read(reader, true, ref fillStyleBits, ref lineStyleBits);
                if (!(record is EndShapeRecord))
                {
                    shapeRecords.Add(record);
                }
            } while (!(record is EndShapeRecord));
        }

        public static void ReadToShapeRecordsRGBA(this ISwfStreamReader reader, List<IShapeRecordRGBA> shapeRecords) {
            var fillStyleBits = reader.ReadUnsignedBits(4);
            var lineStyleBits = reader.ReadUnsignedBits(4);
            reader.AlignToByte();
            IShapeRecordRGBA record;
            do {
                record = _shapeRecordRGBAReader.Read(reader, true, ref fillStyleBits, ref lineStyleBits);
                if (!(record is EndShapeRecord))
                {
                    shapeRecords.Add(record);
                }
            } while (!(record is EndShapeRecord));
        }

        public static void ReadToShapeRecordsEx(this ISwfStreamReader reader, List<IShapeRecordEx> shapeRecords) {
            var fillStyleBits = reader.ReadUnsignedBits(4);
            var lineStyleBits = reader.ReadUnsignedBits(4);
            reader.AlignToByte();
            IShapeRecordEx record;
            do {
                record = _shapeRecorExReader.Read(reader, true, ref fillStyleBits, ref lineStyleBits);
                if (!(record is EndShapeRecord))
                {
                    shapeRecords.Add(record);
                }
            } while (!(record is EndShapeRecord));
        }



    }
}
