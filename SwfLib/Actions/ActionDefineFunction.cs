using System.Collections.Generic;

namespace SwfLib.Actions {
    /// <summary>
    /// Represents DefineFunction action.
    /// </summary>
    public class ActionDefineFunction : ActionBase {

        /// <summary>
        /// Gets or sets function name.
        /// </summary>
        public string Name { get; set; }

        public readonly List<string> Args = new List<string>();

        public int CodeSize { get; set; }

        /// <summary>
        /// Gets code of action.
        /// </summary>
        public override ActionCode ActionCode {
            get { return ActionCode.DefineFunction; }
        }

        public override TResult AcceptVisitor<TArg, TResult>(IActionVisitor<TArg, TResult> visitor, TArg arg) {
            return visitor.Visit(this, arg);
        }
        public override void SetLabel(int pos, List<ActionBase> actions)
        {
            int offset = CodeSize;
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
                CodeSize = actions[j].LocalLabel;
            }
        }
    }
}
