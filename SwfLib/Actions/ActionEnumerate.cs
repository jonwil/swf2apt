﻿namespace SwfLib.Actions {
    /// <summary>
    /// Represents Enumerate action.
    /// </summary>
    public class ActionEnumerate : ActionBase {

        /// <summary>
        /// Gets code of action.
        /// </summary>
        public override ActionCode ActionCode {
            get { return ActionCode.Enumerate; }
        }

        public override TResult AcceptVisitor<TArg, TResult>(IActionVisitor<TArg, TResult> visitor, TArg arg) {
            return visitor.Visit(this, arg);
        }

    }
}
