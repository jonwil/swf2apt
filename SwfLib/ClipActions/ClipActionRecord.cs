using System.Collections.Generic;
using SwfLib.Actions;

namespace SwfLib.ClipActions {
    public class ClipActionRecord {

        public uint Flags;

        public ClipEventFlags EventFlags;

        public byte KeyCode;

        public readonly List<ActionBase> Actions = new List<ActionBase>();

    }
}
