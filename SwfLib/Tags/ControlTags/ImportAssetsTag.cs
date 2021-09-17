using System.Collections.Generic;

namespace SwfLib.Tags.ControlTags {
    public class ImportAssetsTag : ImportAssetsBase {

        public override SwfTagType TagType {
            get { return SwfTagType.ImportAssets; }
        }

        public override TResult AcceptVistor<TArg, TResult>(ISwfTagVisitor<TArg, TResult> visitor, TArg arg) {
            return visitor.Visit(this, arg);
        }
        public override bool IsControlTag => true;
    }
}
