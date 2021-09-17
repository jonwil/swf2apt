using System.Collections.Generic;
namespace SwfLib.Actions {
    /// <summary>
    /// Represents WaitForFrame2 action.
    /// </summary>
    public class ActionWaitForFrame2 : ActionBase {

        /// <summary>
        /// Gets or sets count of frames to be skipped.
        /// </summary>
        public int SkipCount { get; set; }

        /// <summary>
        /// Gets code of action.
        /// </summary>
        public override ActionCode ActionCode {
            get { return ActionCode.WaitForFrame2; }
        }

        public override TResult AcceptVisitor<TArg, TResult>(IActionVisitor<TArg, TResult> visitor, TArg arg) {
            return visitor.Visit(this, arg);
        }
        public override void SetLabel(int pos, List<ActionBase> actions)
        {
            var dest = actions[pos + SkipCount + 1];
            SkipCount = dest.LocalLabel;
        }
    }
}
