using System.Collections.Generic;

namespace SwfLib.Actions {
    /// <summary>
    /// Represents DefineFunction2 action.
    /// </summary>
    public class ActionDefineFunction2 : ActionBase {

        /// <summary>
        /// Gets or sets function name.
        /// </summary>
        public string Name { get; set; }

        public ushort Flags { get; set; }
        /// <summary>
        /// Gets or sets registers count.
        /// </summary>
        public byte RegisterCount { get; set; }

        public bool PreloadParent { get; set; }

        public bool PreloadRoot { get; set; }

        public bool SuppressSuper { get; set; }

        public bool PreloadSuper { get; set; }

        public bool SuppressArguments { get; set; }

        public bool PreloadArguments { get; set; }

        public bool SuppressThis { get; set; }

        public bool PreloadThis { get; set; }

        public byte Reserved { get; set; }

        public bool PreloadGlobal { get; set; }

        public readonly List<RegisterParam> Parameters = new List<RegisterParam>();

        public int CodeSize { get; set; }

        /// <summary>
        /// Gets code of action.
        /// </summary>
        public override ActionCode ActionCode {
            get { return ActionCode.DefineFunction2; }
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
