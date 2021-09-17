using System.Collections.Generic;

namespace SwfLib.Gradients {
    public class BaseGradientRGBA {

        public SpreadMode SpreadMode;

        public InterpolationMode InterpolationMode;

        public readonly List<GradientRecordRGBA> GradientRecords = new List<GradientRecordRGBA>();


    }
}
