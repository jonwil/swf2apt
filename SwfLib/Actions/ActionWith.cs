using System.Collections.Generic;

namespace SwfLib.Actions {
    /// <summary>
    /// represents With action
    /// </summary>
    public class ActionWith : ActionBase {
        
        public int CodeSize { get; set; }

        /// <summary>
        /// Gets code of action.
        /// </summary>
        public override ActionCode ActionCode {
            get { return ActionCode.With; }
        }

        /// <summary>
        /// Accept visitor.
        /// </summary>
        /// <typeparam name="TArg">Type of argument to be passed to visitor.</typeparam>
        /// <typeparam name="TResult">Type of result.</typeparam>
        /// <param name="visitor">Visitor.</param>
        /// <param name="arg">Argument to be passed to visitor.</param>
        /// <returns></returns>
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
