﻿namespace SwfLib.Actions {
    /// <summary>
    /// Represents InstanceOf action.
    /// </summary>
    public class ActionInstanceOf : ActionBase {

        /// <summary>
        /// Gets code of action.
        /// </summary>
        public override ActionCode ActionCode {
            get { return ActionCode.InstanceOf; }
        }

        public override TResult AcceptVisitor<TArg, TResult>(IActionVisitor<TArg, TResult> visitor, TArg arg) {
            return visitor.Visit(this, arg);
        }
    }
}
