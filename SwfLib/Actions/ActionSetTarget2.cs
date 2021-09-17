﻿namespace SwfLib.Actions {
    /// <summary>
    /// Represents SetTarget2 action.
    /// </summary>
    public class ActionSetTarget2 : ActionBase {

        /// <summary>
        /// Gets code of action.
        /// </summary>
        public override ActionCode ActionCode {
            get { return ActionCode.SetTarget2; }
        }

        public override TResult AcceptVisitor<TArg, TResult>(IActionVisitor<TArg, TResult> visitor, TArg arg) {
            return visitor.Visit(this, arg);
        }

    }
}
