namespace SwfLib.Shapes.FillStyles {
    public interface IFillStyleRGBAVisitor<TArg, TResult> {

        TResult Visit(SolidFillStyleRGBA fillStyle, TArg arg);

        TResult Visit(SolidMorphFillStyleRGBA fillStyle, TArg arg);

        TResult Visit(LinearGradientFillStyleRGBA fillStyle, TArg arg);

        TResult Visit(RadialGradientFillStyleRGBA fillStyle, TArg arg);

        TResult Visit(BitmapFillStyleRGBA fillStyle, TArg arg);

        TResult Visit(BitmapMorphFillStyleRGBA fillStyle, TArg arg);

    }
}
