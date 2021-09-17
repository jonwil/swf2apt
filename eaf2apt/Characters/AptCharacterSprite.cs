using SwfLib.Tags;

namespace eaf2apt.Characters
{
    class AptCharacterSprite : AptCharacter
    {
        public AptMovie movie;
        public override void OutputCharacter(int i)
        {
            base.OutputCharacter(i);
            GlobalData.output.Write(3, (int)AptCharacterType.Sprite);
            GlobalData.output.Write(3, 0x09876543);
            movie.WriteMovieFrames();
        }
        public AptCharacterSprite(DefineSpriteTag tag, Globals globaldata) : base(globaldata, tag.TagID)
        {
            movie = new(tag.Tags, globaldata);
        }
    }
}