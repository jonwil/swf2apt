using System.Collections.Generic;

namespace SwfLib.Fonts {
    public class ZoneRecord {

        public readonly List<ZoneData> Data = new List<ZoneData>();

        public byte Reserved;

        public bool ZoneX;

        public bool ZoneY;

    }
}
