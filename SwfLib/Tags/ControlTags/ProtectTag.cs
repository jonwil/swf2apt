﻿namespace SwfLib.Tags.ControlTags {
    public class ProtectTag : ControlBaseTag {

        public override SwfTagType TagType {
            get { return SwfTagType.Protect; }
        }

        public override TResult AcceptVistor<TArg, TResult>(ISwfTagVisitor<TArg, TResult> visitor, TArg arg) {
            return visitor.Visit(this, arg);
        }
        public override bool IsControlTag => true;
    }
}
