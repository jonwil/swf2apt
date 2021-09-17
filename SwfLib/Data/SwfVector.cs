using System;
namespace SwfLib.Data {
    public struct SwfVector {

        public int X;

        public int Y;

        public override bool Equals(object obj)
        {
            return obj is SwfVector vector &&
                   X == vector.X &&
                   Y == vector.Y;
        }

        public override int GetHashCode()
        {
            return HashCode.Combine(X, Y);
        }
    }
}
