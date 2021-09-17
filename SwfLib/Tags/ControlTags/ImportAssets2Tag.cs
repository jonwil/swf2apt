using System.Collections.Generic;

namespace SwfLib.Tags.ControlTags {
    public class ImportAssets2Tag : ImportAssetsBase {
        public override SwfTagType TagType {
            get { return SwfTagType.ImportAssets2; }
        }

        public override TResult AcceptVistor<TArg, TResult>(ISwfTagVisitor<TArg, TResult> visitor, TArg arg) {
            return visitor.Visit(this, arg);
        }
        public override bool IsControlTag => true;
    }
}
