﻿using SwfLib.Data;
using SwfLib.Gradients;

namespace SwfLib.Shapes.FillStyles {
    public class FillStyleRGBAReader : IFillStyleRGBAVisitor<ISwfStreamReader, FillStyleRGBA> {

        private static readonly FillStyleFactory _factory = new FillStyleFactory();

        public FillStyleRGBA Read(ISwfStreamReader reader, FillStyleType type) {
            var fillStyle = _factory.CreateRGBA(type);
            fillStyle.AcceptVisitor(this, reader);
            return fillStyle;
        }
        public FillStyleRGBA ReadMorph(ISwfStreamReader reader, FillStyleType type)
        {
            var fillStyle = _factory.CreateMorphRGBA(type);
            fillStyle.AcceptVisitor(this, reader);
            return fillStyle;
        }

        public FillStyleRGBA Visit(SolidFillStyleRGBA fillStyle, ISwfStreamReader reader) {
            fillStyle.Color = reader.ReadRGBA();
            return fillStyle;
        }
        public FillStyleRGBA Visit(SolidMorphFillStyleRGBA fillStyle, ISwfStreamReader reader)
        {
            fillStyle.StartColor = reader.ReadRGBA();
            fillStyle.EndColor = reader.ReadRGBA();
            return fillStyle;
        }

        public FillStyleRGBA Visit(LinearGradientFillStyleRGBA fillStyle, ISwfStreamReader reader) {
            fillStyle.GradientMatrix = reader.ReadMatrix();
            fillStyle.Gradient = reader.ReadGradientRGBA();
            return fillStyle;
        }

        public FillStyleRGBA Visit(RadialGradientFillStyleRGBA fillStyle, ISwfStreamReader reader) {
            fillStyle.GradientMatrix = reader.ReadMatrix();
            fillStyle.Gradient = reader.ReadGradientRGBA();
            return fillStyle;
        }

        public FillStyleRGBA Visit(BitmapFillStyleRGBA fillStyle, ISwfStreamReader reader) {
            fillStyle.BitmapID = reader.ReadUInt16();
            fillStyle.BitmapMatrix = reader.ReadMatrix();
            return fillStyle;
        }

        public FillStyleRGBA Visit(BitmapMorphFillStyleRGBA fillStyle, ISwfStreamReader reader)
        {
            fillStyle.BitmapID = reader.ReadUInt16();
            fillStyle.StartBitmapMatrix = reader.ReadMatrix();
            fillStyle.EndBitmapMatrix = reader.ReadMatrix();
            return fillStyle;
        }
    }
}
