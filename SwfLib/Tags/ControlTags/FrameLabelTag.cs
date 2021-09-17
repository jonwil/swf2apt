﻿namespace SwfLib.Tags.ControlTags {
    public class FrameLabelTag : ControlBaseTag {
        
        public string Name { get; set; }

        public byte? AnchorFlag;

        public override SwfTagType TagType {
            get { return SwfTagType.FrameLabel; }
        }

        public override TResult AcceptVistor<TArg, TResult>(ISwfTagVisitor<TArg, TResult> visitor, TArg arg) {
            return visitor.Visit(this, arg);
        }
        public override bool IsControlTag => true;
    }
}