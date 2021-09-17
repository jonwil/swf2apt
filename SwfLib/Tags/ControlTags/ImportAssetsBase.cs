using System.Collections.Generic;

namespace SwfLib.Tags.ControlTags
{
    public abstract class ImportAssetsBase : ControlBaseTag
    {
        public string URL { get; set; }

        public List<ushort> Tags = new List<ushort>();

        public List<string> Names = new List<string>();

    }
}
