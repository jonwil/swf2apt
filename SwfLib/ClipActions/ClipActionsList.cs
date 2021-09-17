using System.Collections.Generic;

namespace SwfLib.ClipActions {
    public class ClipActionsList {

        public ushort Reserved;

        //TODO: this is calculated field actually
        public ClipEventFlags Flags;

        public readonly List<ClipActionRecord> Records = new List<ClipActionRecord>();
    }
}
