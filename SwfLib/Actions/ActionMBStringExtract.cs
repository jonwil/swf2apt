﻿namespace SwfLib.Actions {
    public class ActionMBStringExtract : ActionBase {

        public override ActionCode ActionCode {
            get { return ActionCode.MBStringExtract; }
        }

        public override TResult AcceptVisitor<TArg, TResult>(IActionVisitor<TArg, TResult> visitor, TArg arg) {
            return visitor.Visit(this, arg);
        }

    }
}
