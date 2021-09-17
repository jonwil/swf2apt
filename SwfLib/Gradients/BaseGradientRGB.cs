﻿using System.Collections.Generic;

namespace SwfLib.Gradients {
    public class BaseGradientRGB {

        public SpreadMode SpreadMode;

        public InterpolationMode InterpolationMode;

        public readonly List<GradientRecordRGB> GradientRecords = new List<GradientRecordRGB>();

    }
}
