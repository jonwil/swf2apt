using System.Collections.Generic;

namespace SwfLib.Actions {
    /// <summary>
    /// Represents Try action.
    /// </summary>
    public class ActionTry : ActionBase {

        public byte Flags { get; set; }
        public byte Reserved { get; set; }

        public bool CatchInRegister { get; set; }

        public bool FinallyBlock { get; set; }

        public bool CatchBlock { get; set; }

        public string CatchName { get; set; }

        public byte CatchRegister { get; set; }

        public int TrySize { get; set; }
        public int CatchSize { get; set; }
        public int FinallySize { get; set; }

        /// <summary>
        /// Gets code of action.
        /// </summary>
        public override ActionCode ActionCode {
            get { return ActionCode.Try; }
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
            int j = pos + 1;
            int offset = TrySize;
            if (offset > 0)
            {
                int set = actions[j].LocalLabel;
                int dst = set;
                while (j < actions.Count && (dst - set) < offset)
                {
                    j++;
                    dst = actions[j].LocalLabel;
                }
                if (dst - set == offset)
                {
                    TrySize = actions[j].LocalLabel;
                }
            }
            offset = CatchSize;
            if (offset > 0)
            {
                int set = actions[j].LocalLabel;
                int dst = set;
                while (j < actions.Count && (dst - set) < offset)
                {
                    j++;
                    dst = actions[j].LocalLabel;
                }
                if (dst - set == offset)
                {
                    CatchSize = actions[j].LocalLabel;
                }
            }
            offset = FinallySize;
            if (offset > 0)
            {
                int set = actions[j].LocalLabel;
                int dst = set;
                while (j < actions.Count && (dst - set) < offset)
                {
                    j++;
                    dst = actions[j].LocalLabel;
                }
                if (dst - set == offset)
                {
                    FinallySize = actions[j].LocalLabel;
                }
            }
        }
    }
}
