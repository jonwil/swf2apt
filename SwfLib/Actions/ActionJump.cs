using System.Collections.Generic;
namespace SwfLib.Actions {
    public class ActionJump : ActionBase {

        public int BranchOffset { get; set; }

        /// <summary>
        /// Gets code of action.
        /// </summary>
        public override ActionCode ActionCode {
            get { return ActionCode.Jump; }
        }

        public override TResult AcceptVisitor<TArg, TResult>(IActionVisitor<TArg, TResult> visitor, TArg arg) {
            return visitor.Visit(this, arg);
        }
        public override void SetLabel(int pos, List<ActionBase> actions)
        {
            int offset = BranchOffset;
            int j = pos + 1;
            int set = actions[j].LocalLabel;
            int dst = set;
            if (offset < 0)
            {
                while (j >= 0 && (dst - set) > offset)
                {
                    j--;
                    dst = actions[j].LocalLabel;
                }
            }
            else
            {
                while (j < actions.Count && (dst - set) < offset)
                {
                    j++;
                    dst = actions[j].LocalLabel;
                }
            }
            if (dst - set == offset)
            {
                BranchOffset = actions[j].LocalLabel;
            }
        }
    }
}
