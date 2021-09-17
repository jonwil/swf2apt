﻿using System.Collections.Generic;
using SwfLib.Text;

namespace SwfLib.Tags.TextTags {
    public class DefineTextTag : DefineTextBaseTag {

        public readonly List<TextRecordRGB> TextRecords = new List<TextRecordRGB>();

        public override SwfTagType TagType {
            get { return SwfTagType.DefineText; }
        }

        public override TResult AcceptVistor<TArg, TResult>(ISwfTagVisitor<TArg, TResult> visitor, TArg arg) {
            return visitor.Visit(this, arg);
        }
        public override int TagID => CharacterID;
    }
}
