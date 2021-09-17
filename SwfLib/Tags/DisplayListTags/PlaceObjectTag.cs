﻿using SwfLib.Data;

namespace SwfLib.Tags.DisplayListTags {
    public class PlaceObjectTag : PlaceObjectBaseTag {

        public ColorTransformRGB? ColorTransform;

        public override SwfTagType TagType {
            get { return SwfTagType.PlaceObject; }
        }

        public override TResult AcceptVistor<TArg, TResult>(ISwfTagVisitor<TArg, TResult> visitor, TArg arg) {
            return visitor.Visit(this, arg);
        }
        public override bool IsControlTag => true;
    }
}
