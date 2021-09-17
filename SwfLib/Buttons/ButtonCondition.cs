using System.Collections.Generic;
using SwfLib.Actions;

namespace SwfLib.Buttons {
    public class ButtonCondition {

        public ushort Conditions { get; set; }
        public bool IdleToOverDown { get; set; }

        public bool OutDownToIdle { get; set; }

        public bool OutDownToOverDown { get; set; }

        public bool OverDownToOutDown { get; set; }

        public bool OverDownToOverUp { get; set; }

        public bool OverUpToOverDown { get; set; }

        public bool OverUpToIdle { get; set; }

        public bool IdleToOverUp { get; set; }

        public byte KeyPress { get; set; }

        public bool OverDownToIdle { get; set; }

        /// <summary>
        /// Gets list of actions.
        /// </summary>
        public readonly List<ActionBase> Actions = new List<ActionBase>();
    }
}
