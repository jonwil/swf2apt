using SwfLib.Data;

namespace SwfLib.Tags.ShapeMorphingTags {
    public abstract class ShapeMorphingBaseTag : SwfTagBase {
        public ushort CharacterID { get; set; }
        public SwfRect StartBounds { get; set; }
        public SwfRect EndBounds { get; set; }
    }
}
