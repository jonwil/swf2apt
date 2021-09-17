using SwfLib.Data;
using SwfLib.Gradients;
using SwfLib.Shapes.FillStyles;
using SwfLib.Shapes.LineStyles;
using SwfLib.Shapes.Records;
using SwfLib.Tags.ShapeTags;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Text.RegularExpressions;

namespace eaf2apt.Characters
{
    public struct FloatVector
    {

        public double X;

        public double Y;

        public override bool Equals(object obj)
        {
            return obj is FloatVector vector &&
                   X == vector.X &&
                   Y == vector.Y;
        }

        public override int GetHashCode()
        {
            return HashCode.Combine(X, Y);
        }
    }
    public class EqualityComparerRGBA : IEqualityComparer<List<GradientRecordRGBA>>
    {
        public bool Equals(List<GradientRecordRGBA> x, List<GradientRecordRGBA> y)
        {
            if (x.Count != y.Count)
            {
                return false;
            }
            for (int i = 0; i < x.Count; i++)
            {
                if (!x[i].Equals(y[i]))
                {
                    return false;
                }
            }
            return true;
        }

        public int GetHashCode(List<GradientRecordRGBA> obj)
        {
            int result = 17;
            for (int i = 0; i < obj.Count; i++)
            {
                unchecked
                {
                    result = result * 23 + obj[i].GetHashCode();
                }
            }
            return result;
        }
    }
    class ShapeEdge
    {
        public FloatVector from;
        public FloatVector to;
        public bool linevalid;
        public ILineStyle line;
        public bool fill0valid;
        public IFillStyle fill0;
        public bool fill1valid;
        public IFillStyle fill1;
    }

    class ShapeEdgeData
    {
        public ShapeEdge edge;
        public FloatVector opposite;
    }
    class ShapePotentialTriangle
    {
        public FloatVector[] points = new FloatVector[3];
        public int[] pointindices = new int[3];
        public int[] neighbors = new int[3];
        public List<ShapeEdgeData> edgedata = new();
    }

    class ShapeLine
    {
        public FloatVector from;
        public FloatVector to;
        public ILineStyle style;
    }

    class ShapeTriangle
    {
        public FloatVector a;
        public FloatVector b;
        public FloatVector c;
        public IFillStyle fill;
    }

    class Shape
    {
        public List<ShapeLine> lines = new();
        public List<ShapeTriangle> triangles = new();
    }

    class AptCharacterShape : AptCharacter
    {
        public AptRect BoundingRect;
        double PI = 3.1415926535;
        public int? CurLineStyleIndex;
        public int? CurFillStyle0Index;
        public int? CurFillStyle1Index;
        public int outid;
        public bool empty;
        public List<Shape> shapes = new();

        public bool IsLeftVector(FloatVector v0, FloatVector v1, FloatVector v2)
        {
            double dx1 = v1.X - v0.X;
            double dy1 = v1.Y - v0.Y;
            double dx2 = v2.X - v1.X;
            double dy2 = v2.Y - v1.Y;
            double angle1 = Math.Atan2(dy1, dx1);
            double angle2 = Math.Atan2(dy2, dx2);
            double dangle = angle1 - angle2;
            if (dangle > PI)
            {
                dangle -= 2 * PI;
            }
            if (dangle < -PI)
            {
                dangle += 2 * PI;
            }
            if (dangle > 0)
            {
                return true;
            }
            return false;
        }

        FloatVector FindEarliestPoint(FloatVector v, Dictionary<String, FloatVector> points)
        {
            string lookup = $"{v.X}_{v.Y}";
            if (points.ContainsKey(lookup))
            {
                return points[lookup];
            }
            points[lookup] = v;
            return v;
        }

        void BuildCurvePoints(int subdivisions, List<ShapeEdge> edges, Dictionary<String, FloatVector> points, FloatVector a1, FloatVector control, FloatVector a2, ILineStyle line, bool hasline, IFillStyle fill0, bool hasfill0, IFillStyle fill1, bool hasfill1)
        {
            if (subdivisions != 0)
            {
                double minx, maxx, miny, maxy;
                if (a1.X < control.X)
                {
                    minx = a1.X;
                    maxx = control.X;
                }
                else
                {
                    minx = control.X;
                    maxx = a1.X;
                }
                if (a2.X < minx)
                {
                    minx = a2.X;
                }
                if (a2.X > maxx)
                {
                    maxx = a2.X;
                }
                if (a1.Y < control.Y)
                {
                    miny = a1.Y;
                    maxy = control.Y;
                }
                else
                {
                    miny = control.Y;
                    maxy = a1.Y;
                }
                if (a2.Y < miny)
                {
                    miny = a2.Y;
                }
                if (a2.Y > maxy)
                {
                    maxy = a2.Y;
                }
                if ((maxx - minx) > 30 && (maxy - miny) > 30)
                {
                    FloatVector v1;
                    v1.X = (a1.X + control.X) / 2;
                    v1.Y = (a1.Y + control.Y) / 2;
                    FloatVector v2;
                    v2.X = (a2.X + control.X) / 2;
                    v2.Y = (a2.Y + control.Y) / 2;
                    var c1 = FindEarliestPoint(v1, points);
                    var c2 = FindEarliestPoint(v2, points);
                    FloatVector v3;
                    v3.X = (c1.X + c2.X) / 2;
                    v3.Y = (c1.Y + c2.Y) / 2;
                    var p = FindEarliestPoint(v3, points);
                    subdivisions--;
                    BuildCurvePoints(subdivisions, edges, points, a1, c1, p, line, hasline, fill0, hasfill0, fill1, hasfill1);
                    BuildCurvePoints(subdivisions, edges, points, p, c2, a2, line, hasline, fill0, hasfill0, fill1, hasfill1);
                    return;
                }
            }
            edges.Add(new ShapeEdge { from = a2, to = control, linevalid = hasline, line = line, fill0valid = hasfill0, fill0 = fill0, fill1valid = hasfill1, fill1 = fill1 });
            edges.Add(new ShapeEdge { from = control, to = a1, linevalid = hasline, line = line, fill0valid = hasfill0, fill0 = fill0, fill1valid = hasfill1, fill1 = fill1 });
        }

        bool FindEdgeForTriangle(ShapePotentialTriangle tri, List<ShapePotentialTriangle> trilist, out ShapeEdgeData data)
        {
            Dictionary<int, bool> visited = new();
            again:
            if (tri.edgedata.Count > 0)
            {
                data = tri.edgedata[0];
                return true;
            }
            for (int i = 0; i < 3; i++)
            {
                int neighbor = tri.neighbors[i];
                if (neighbor == -1)
                {
                    data = new();
                    return false;
                }
                if (visited.ContainsKey(neighbor))
                {
                    continue;
                }
                visited[neighbor] = true;
                tri = trilist[neighbor];
                goto again;
            }
            data = new();
            return false;
        }

        void MakeTris(Shape shape, List<ShapeEdge> edges)
        {
            Dictionary<FloatVector, int> pointhash = new();
            List<FloatVector> points = new();
            List<ShapePotentialTriangle> potentialtriangles = new();
            for (int i = 0; i < edges.Count; i++)
            {
                if (!pointhash.ContainsKey(edges[i].from))
                {
                    points.Add(edges[i].from);
                    pointhash[edges[i].from] = points.Count - 1;
                }
                if (!pointhash.ContainsKey(edges[i].to))
                {
                    points.Add(edges[i].to);
                    pointhash[edges[i].to] = points.Count - 1;
                }
            }
            if (points.Count < 3)
            {
                return;
            }
            string fname = "triangletemp";
            Random r = new();
            int number = r.Next(0, 500000);
            while (File.Exists(fname + number + ".poly") || File.Exists(fname + number + ".1.node") || File.Exists(fname + number + ".1.ele") || File.Exists(fname + number + ".1.neigh"))
            {
                number = r.Next(0, 500000);
            }
            string name = fname + number;
            using FileStream ofile = new FileStream(name + ".poly", FileMode.CreateNew);
            {
                using StreamWriter ofilesr = new StreamWriter(ofile);
                {
                    ofilesr.WriteLine(@$"{points.Count} 2 0 0");
                    for (int i = 0; i < points.Count; i++)
                    {
                        ofilesr.WriteLine(@$"{i} {points[i].X} {points[i].Y}");
                    }
                    ofilesr.WriteLine(@$"{edges.Count} 0");
                    for (int i = 0; i < edges.Count; i++)
                    {
                        int f = pointhash[edges[i].from];
                        int t = pointhash[edges[i].to];
                        ofilesr.WriteLine(@$"{i} {f} {t}");
                    }
                    ofilesr.WriteLine("0");
                }
            }
            var process = Process.Start("triangle", @$"-Q -P -c -n -p {name}.poly");
            process.WaitForExit();
            using FileStream node = new FileStream(name + ".1.node", FileMode.Open);
            {
                using FileStream ele = new FileStream(name + ".1.ele", FileMode.Open);
                {
                    using FileStream neigh = new FileStream(name + ".1.neigh", FileMode.Open);
                    {
                        using StreamReader noder = new StreamReader(node);
                        {
                            using StreamReader eler = new StreamReader(ele);
                            {
                                using StreamReader neighr = new StreamReader(neigh);
                                {
                                    string nodeheader = noder.ReadLine();
                                    string eleheader = eler.ReadLine();
                                    string neighheader = neighr.ReadLine();
                                    string[] nodeheaders = Regex.Split(nodeheader, "\\s+");
                                    string[] eleheaders = Regex.Split(eleheader, "\\s+");
                                    string[] neighheaders = Regex.Split(neighheader, "\\s+");
                                    int vertices = Convert.ToInt32(nodeheaders[0]);
                                    if (points.Count != vertices)
                                    {
                                        for (int i = 0; i < vertices; i++)
                                        {
                                            string nodel = noder.ReadLine();
                                            nodel = nodel.TrimStart();
                                            string[] coords = Regex.Split(nodel, "\\s+");
                                            if (i >= points.Count)
                                            {
                                                FloatVector v;
                                                v.X = Convert.ToDouble(coords[1]);
                                                v.Y = Convert.ToDouble(coords[2]);
                                                points.Add(v);
                                            }
                                        }
                                    }
                                    int triangles = Convert.ToInt32(eleheaders[0]);
                                    for (int i = 0; i < triangles; i++)
                                    {
                                        string elel = eler.ReadLine();
                                        string neighl = neighr.ReadLine();
                                        elel = elel.TrimStart();
                                        neighl = neighl.TrimStart();
                                        string[] verts = Regex.Split(elel, "\\s+");
                                        string[] neighs = Regex.Split(neighl, "\\s+");
                                        ShapePotentialTriangle triangle = new();
                                        triangle.points[0] = points[Convert.ToInt32(verts[1])];
                                        triangle.points[1] = points[Convert.ToInt32(verts[2])];
                                        triangle.points[2] = points[Convert.ToInt32(verts[3])];
                                        triangle.pointindices[0] = Convert.ToInt32(verts[1]);
                                        triangle.pointindices[1] = Convert.ToInt32(verts[2]);
                                        triangle.pointindices[2] = Convert.ToInt32(verts[3]);
                                        triangle.neighbors[0] = Convert.ToInt32(neighs[1]);
                                        triangle.neighbors[1] = Convert.ToInt32(neighs[2]);
                                        triangle.neighbors[2] = Convert.ToInt32(neighs[3]);
                                        potentialtriangles.Add(triangle);
                                    }
                                }
                            }
                        }
                    }
                }
            }
            File.Delete(name + ".poly");
            File.Delete(name + ".1.node");
            File.Delete(name + ".1.ele");
            File.Delete(name + ".1.neigh");
            Dictionary<int, List<ShapeEdge>> pointtoedge = new();
            for (int i = 0; i < edges.Count; i++)
            {
                var e = edges[i];
                if (!pointtoedge.ContainsKey(pointhash[e.from]))
                {
                    pointtoedge[pointhash[e.from]] = new();
                }
                if (!pointtoedge.ContainsKey(pointhash[e.to]))
                {
                    pointtoedge[pointhash[e.to]] = new();
                }
                pointtoedge[pointhash[e.from]].Add(e);
                pointtoedge[pointhash[e.to]].Add(e);
            }
            foreach (var tri in potentialtriangles)
            {
                for (int i = 0; i < 3; i++)
                {
                    var p = tri.pointindices[i];
                    if (pointtoedge.ContainsKey(p))
                    {
                        var e = pointtoedge[p];
                        foreach (var edge in e)
                        {
                            int count = 0;
                            if (tri.pointindices[0] == pointhash[edge.from])
                            {
                                count++;
                            }
                            if (tri.pointindices[0] == pointhash[edge.to])
                            {
                                count++;
                            }
                            if (tri.pointindices[1] == pointhash[edge.from])
                            {
                                count++;
                            }
                            if (tri.pointindices[1] == pointhash[edge.to])
                            {
                                count++;
                            }
                            if (tri.pointindices[2] == pointhash[edge.from])
                            {
                                count++;
                            }
                            if (tri.pointindices[2] == pointhash[edge.to])
                            {
                                count++;
                            }
                            if (count >= 2)
                            {
                                FloatVector opposite;
                                opposite.X = -1;
                                opposite.Y = -1;
                                if (tri.pointindices[0] != pointhash[edge.from] && tri.pointindices[0] != pointhash[edge.to])
                                {
                                    opposite = tri.points[0];
                                }
                                if (tri.pointindices[1] != pointhash[edge.from] && tri.pointindices[1] != pointhash[edge.to])
                                {
                                    opposite = tri.points[1];
                                }
                                if (tri.pointindices[2] != pointhash[edge.from] && tri.pointindices[2] != pointhash[edge.to])
                                {
                                    opposite = tri.points[2];
                                }
                                tri.edgedata.Add(new ShapeEdgeData { edge = edge, opposite = opposite });
                            }
                        }
                    }
                }
            }
            pointtoedge.Clear();
            for (int i = 0; i < potentialtriangles.Count; i++)
            {
                if (FindEdgeForTriangle(potentialtriangles[i], potentialtriangles, out var edge))
                {
                    IFillStyle fill;
                    bool fillvalid;
                    if (IsLeftVector(edge.edge.from, edge.edge.to, edge.opposite))
                    {
                        fill = edge.edge.fill0;
                        fillvalid = edge.edge.fill0valid;
                    }
                    else
                    {
                        fill = edge.edge.fill1;
                        fillvalid = edge.edge.fill1valid;
                    }
                    if (fillvalid)
                    {
                        shape.triangles.Add(new ShapeTriangle { a = potentialtriangles[i].points[0], b = potentialtriangles[i].points[1], c = potentialtriangles[i].points[2], fill = fill });
                    }
                }
            }
        }


        byte[] MakeLinearGradient(List<GradientRecordRGBA> gradients)
        {
            byte[] imagedata = new byte[256 * 4];
            double curr = gradients[0].Color.Red;
            double curg = gradients[0].Color.Green;
            double curb = gradients[0].Color.Blue;
            double cura = gradients[0].Color.Alpha;
            double deltar = 0;
            double deltag = 0;
            double deltab = 0;
            double deltaa = 0;
            for (int i = 0; i < 256; i++)
            {
                for (int j = 0; j < gradients.Count; j++)
                {
                    var grad = gradients[j];
                    if (grad.Ratio == i)
                    {
                        curr = grad.Color.Red;
                        curg = grad.Color.Green;
                        curb = grad.Color.Blue;
                        cura = grad.Color.Alpha;

                        deltar = 0;
                        deltag = 0;
                        deltab = 0;
                        deltaa = 0;

                        if (j < gradients.Count - 1)
                        {
                            var nextgrad = gradients[j + 1];
                            var pixels = nextgrad.Ratio - grad.Ratio;
                            if (pixels != 0)
                            {
                                deltar = (nextgrad.Color.Red - curr) / pixels;
                                deltag = (nextgrad.Color.Green - curg) / pixels;
                                deltab = (nextgrad.Color.Blue - curb) / pixels;
                                deltaa = (nextgrad.Color.Alpha - cura) / pixels;
                            }
                        }
                    }
                }

                imagedata[(i * 4)] = (byte)Math.Floor(curb);
                imagedata[(i * 4) + 1] = (byte)Math.Floor(curg);
                imagedata[(i * 4) + 2] = (byte)Math.Floor(curr);
                imagedata[(i * 4) + 3] = (byte)Math.Floor(cura);
                curr += deltar;
                curg += deltag;
                curb += deltab;
                cura += deltaa;
            }
            return imagedata;
        }
        byte[] MakeRadialGradientFromLinear(byte[] linear, ushort size)
        {
            byte[] radial = new byte[size * size * 4];
            double midpoint = ((double)(size - 1)) / 2;
            double indexscale = 255 / midpoint;
            for (int i = 0; i < size; i++)
            {
                double y = i - midpoint;
                for (int j = 0; j < size; j++)
                {
                    double x = j - midpoint;
                    double dist = Math.Sqrt(x * x + y * y);
                    double index = indexscale * dist;
                    byte clampedindex = (byte)(index > 255 ? 255 : index);
                    radial[i * size * 4 + j * 4 + 0] = linear[clampedindex * 4 + 0];
                    radial[i * size * 4 + j * 4 + 1] = linear[clampedindex * 4 + 1];
                    radial[i * size * 4 + j * 4 + 2] = linear[clampedindex * 4 + 2];
                    radial[i * size * 4 + j * 4 + 3] = linear[clampedindex * 4 + 3];
                }
            }
            return radial;
        }

        void ConvertFillStyles(List<FillStyleRGB> filllist, List<FillStyleRGBA> filllist2)
        {
            foreach (var fs in filllist)
            {
                switch (fs)
                {
                    case BitmapFillStyleRGB bitmap:
                        {
                            var f2 = new BitmapFillStyleRGBA();
                            f2.BitmapID = bitmap.BitmapID;
                            f2.BitmapMatrix = bitmap.BitmapMatrix;
                            f2.Mode = bitmap.Mode;
                            f2.Smoothing = bitmap.Smoothing;
                            filllist2.Add(f2);
                        }
                        break;
                    case LinearGradientFillStyleRGB linear:
                        {
                            var f2 = new LinearGradientFillStyleRGBA();
                            f2.BitmapID = linear.BitmapID;
                            f2.Gradient = new();
                            f2.Gradient.InterpolationMode = linear.Gradient.InterpolationMode;
                            f2.Gradient.SpreadMode = linear.Gradient.SpreadMode;
                            f2.GradientMatrix = linear.GradientMatrix;
                            foreach (var gr in linear.Gradient.GradientRecords)
                            {
                                var gr2 = new GradientRecordRGBA();
                                gr2.Ratio = gr.Ratio;
                                gr2.Color = new SwfRGBA(gr.Color);
                                f2.Gradient.GradientRecords.Add(gr2);
                            }
                            filllist2.Add(f2);
                        }
                        break;
                    case RadialGradientFillStyleRGB radial:
                        {
                            var f2 = new RadialGradientFillStyleRGBA();
                            f2.BitmapID = radial.BitmapID;
                            f2.Gradient = new();
                            f2.Gradient.InterpolationMode = radial.Gradient.InterpolationMode;
                            f2.Gradient.SpreadMode = radial.Gradient.SpreadMode;
                            f2.GradientMatrix = radial.GradientMatrix;
                            foreach (var gr in radial.Gradient.GradientRecords)
                            {
                                var gr2 = new GradientRecordRGBA();
                                gr2.Ratio = gr.Ratio;
                                gr2.Color = new SwfRGBA(gr.Color);
                                f2.Gradient.GradientRecords.Add(gr2);
                            }
                            filllist2.Add(f2);
                        }
                        break;
                    case SolidFillStyleRGB solid:
                        {
                            var f2 = new SolidFillStyleRGBA();
                            f2.Color = new SwfRGBA(solid.Color);
                            filllist2.Add(f2);
                        }
                        break;
                }
            }
        }

        void ConvertLineStyles(List<LineStyleRGB> linelist, List<LineStyleRGBA> linelist2)
        {
            foreach (var ls in linelist)
            {
                var ls2 = new LineStyleRGBA();
                ls2.Width = ls.Width;
                ls2.Color = new SwfRGBA(ls.Color);
                linelist2.Add(ls2);
            }
        }

        void BuildShapes(bool type2, List<IShapeRecordRGB> shaperecs, List<FillStyleRGB> filllist, List<LineStyleRGB> linelist, int? curlineindex = null, int? curfill0index = null, int? curfill1index = null)
        {
            List<IShapeRecordRGBA> sr = new();
            foreach (var rec in shaperecs)
            {
                switch (rec)
                {
                    case StyleChangeShapeRecordRGB style:
                        {
                            var r2 = new StyleChangeShapeRecordRGBA();
                            r2.FillStyle0 = style.FillStyle0;
                            r2.FillStyle1 = style.FillStyle1;
                            ConvertFillStyles(style.FillStyles, r2.FillStyles);
                            r2.LineStyle = style.LineStyle;
                            ConvertLineStyles(style.LineStyles, r2.LineStyles);
                            r2.MoveDeltaX = style.MoveDeltaX;
                            r2.MoveDeltaY = style.MoveDeltaY;
                            r2.StateMoveTo = style.StateMoveTo;
                            r2.StateNewStyles = style.StateNewStyles;
                            sr.Add(r2);
                        }
                        break;
                    case CurvedEdgeShapeRecord curved:
                        {
                            sr.Add(curved);
                        }
                        break;
                    case EndShapeRecord end:
                        {
                            sr.Add(end);
                        }
                        break;
                    case StraightEdgeShapeRecord straight:
                        {
                            sr.Add(straight);
                        }
                        break;
                }
            }
            List<FillStyleRGBA> fs = new();
            ConvertFillStyles(filllist, fs);
            List<LineStyleRGBA> ls = new();
            ConvertLineStyles(linelist, ls);
            BuildShapes(type2, sr, fs, ls, curlineindex, curfill0index, curfill1index);
        }

        void BuildShapes(bool type2, List<IShapeRecordRGBA> shaperecs, List<FillStyleRGBA> filllist, List<LineStyleRGBA> linelist, int? curlineindex = null, int? curfill0index = null, int? curfill1index = null)
        {
            Dictionary<string, FloatVector> points = new();
            List<Shape> shapelist = new();
            ILineStyle curlinestyle = new LineStyleRGBA();
            IFillStyle curfillstyle0 = new SolidFillStyleRGBA();
            IFillStyle curfillstyle1 = new SolidFillStyleRGBA();
            bool haslinestyle = false;
            bool hasfillstyle0 = false;
            bool hasfillstyle1 = false;
            List<FillStyleRGBA> fills = new(filllist);
            List<LineStyleRGBA> lines = new(linelist);
            CurLineStyleIndex = curlineindex;
            CurFillStyle0Index = curfill0index;
            CurFillStyle1Index = curfill1index;
            Shape shape = new();
            List<ShapeEdge> edges = new();
            bool last2posvalid = false;
            FloatVector last2pos = new();
            FloatVector v = new FloatVector { X = 0, Y = 0 };
            FloatVector lastpos = FindEarliestPoint(v, points);
            if (CurLineStyleIndex is not null)
            {
                curlinestyle = lines[CurLineStyleIndex.Value];
                haslinestyle = true;
            }
            if (CurFillStyle0Index is not null)
            {
                curfillstyle0 = fills[CurFillStyle0Index.Value];
                hasfillstyle0 = true;
            }
            if (CurFillStyle1Index is not null)
            {
                curfillstyle1 = fills[CurFillStyle1Index.Value];
                hasfillstyle1 = true;
            }
            bool maketris = false;
            for (int i = 0; i < shaperecs.Count; i++)
            {
                var shaperec = shaperecs[i];
                switch (shaperec)
                {
                    case StyleChangeShapeRecordRGBA style:
                        if (type2)
                        {
                            if (style.FillStyles.Count > 0)
                            {
                                fills = new(style.FillStyles);
                            }
                            if (style.LineStyles.Count > 0)
                            {
                                lines = new(style.LineStyles);
                            }
                        }
                        if (style.LineStyle is not null)
                        {
                            CurLineStyleIndex = ((int)style.LineStyle.Value) - 1;
                            if (style.LineStyle.Value > 0)
                            {
                                curlinestyle = lines[CurLineStyleIndex.Value];
                                haslinestyle = true;
                            }
                            else
                            {
                                curlinestyle = new LineStyleRGBA();
                                haslinestyle = false;
                            }
                        }
                        if (style.FillStyle0 is not null)
                        {
                            CurFillStyle0Index = ((int)style.FillStyle0.Value) - 1;
                            if (style.FillStyle0.Value > 0)
                            {
                                curfillstyle0 = fills[CurFillStyle0Index.Value];
                                hasfillstyle0 = true;
                            }
                            else
                            {
                                curfillstyle0 = new SolidFillStyleRGBA();
                                hasfillstyle0 = false;
                            }
                        }
                        if (style.FillStyle1 is not null)
                        {
                            CurFillStyle1Index = ((int)style.FillStyle1.Value) - 1;
                            if (style.FillStyle1.Value > 0)
                            {
                                curfillstyle1 = fills[CurFillStyle1Index.Value];
                                hasfillstyle1 = true;
                            }
                            else
                            {
                                curfillstyle1 = new SolidFillStyleRGBA();
                                hasfillstyle1 = false;
                            }
                        }
                        if (style.StateMoveTo)
                        {
                            if (style.MoveDeltaX == 0 && style.MoveDeltaY == 0)
                            {
                                maketris = true;
                                last2posvalid = false;
                                last2pos = new();
                                FloatVector v2 = new FloatVector { X = style.MoveDeltaX, Y = style.MoveDeltaY };
                                lastpos = FindEarliestPoint(v2, points);
                            }
                            else
                            {
                                last2posvalid = false;
                                last2pos = new();
                                FloatVector v3 = new FloatVector { X = style.MoveDeltaX, Y = style.MoveDeltaY };
                                lastpos = FindEarliestPoint(v3, points);
                            }
                        }
                        break;
                    case StraightEdgeShapeRecord straight:
                        FloatVector v4 = new FloatVector { X = lastpos.X + straight.DeltaX, Y = lastpos.Y + straight.DeltaY };
                        FloatVector newpos = FindEarliestPoint(v4, points);
                        edges.Add(new ShapeEdge { from = lastpos, to = newpos, line = curlinestyle, linevalid = haslinestyle, fill0 = curfillstyle0, fill0valid = hasfillstyle0, fill1 = curfillstyle1, fill1valid = hasfillstyle1 });
                        if (last2posvalid && newpos.X == last2pos.X && newpos.Y == last2pos.Y)
                        {
                            edges[edges.Count - 1].fill0 = new SolidFillStyleRGBA();
                            edges[edges.Count - 1].fill0valid = false;
                            edges[edges.Count - 1].fill1 = new SolidFillStyleRGBA();
                            edges[edges.Count - 1].fill1valid = false;
                            edges[edges.Count - 2].fill0 = new SolidFillStyleRGBA();
                            edges[edges.Count - 2].fill0valid = false;
                            edges[edges.Count - 2].fill1 = new SolidFillStyleRGBA();
                            edges[edges.Count - 2].fill1valid = false;
                        }
                        last2pos = lastpos;
                        last2posvalid = true;
                        lastpos = newpos;
                        break;
                    case CurvedEdgeShapeRecord curved:
                        FloatVector c = new FloatVector { X = lastpos.X + curved.ControlDeltaX, Y = lastpos.Y + curved.ControlDeltaY };
                        FloatVector a = new FloatVector { X = c.X + curved.AnchorDeltaX, Y = c.Y + curved.AnchorDeltaY };
                        var control = FindEarliestPoint(c, points);
                        var anchor = FindEarliestPoint(a, points);
                        BuildCurvePoints(999, edges, points, anchor, control, lastpos, curlinestyle, haslinestyle, curfillstyle0, hasfillstyle0, curfillstyle1, hasfillstyle1);
                        last2pos = lastpos;
                        last2posvalid = true;
                        lastpos = anchor;
                        break;
                }
                if (i == shaperecs.Count - 1)
                {
                    maketris = true;
                }
                if (maketris)
                {
                    foreach (var edge in edges)
                    {
                        if (edge.linevalid)
                        {
                            shape.lines.Add(new ShapeLine { from = edge.from, to = edge.to, style = edge.line });
                        }
                    }
                    MakeTris(shape, edges);
                    maketris = false;
                    shapes.Add(shape);
                    shape = new();
                    edges.Clear();
                    points.Clear();
                }
            }
            Dictionary<List<GradientRecordRGBA>, int> LinearStyles = new(new EqualityComparerRGBA());
            Dictionary<List<GradientRecordRGBA>, int> RadialStyles = new(new EqualityComparerRGBA());
            foreach (var s in shapes)
            {
                foreach (var t in s.triangles)
                {
                    switch (t.fill)
                    {
                        case LinearGradientFillStyleRGBA linear:
                            if (!LinearStyles.ContainsKey(linear.Gradient.GradientRecords))
                            {
                                byte[] image = MakeLinearGradient(linear.Gradient.GradientRecords);
                                byte[] image2 = new byte[image.Length * 4];
                                image.CopyTo(image2, image.Length * 0);
                                image.CopyTo(image2, image.Length * 1);
                                image.CopyTo(image2, image.Length * 2);
                                image.CopyTo(image2, image.Length * 3);
                                int id = GlobalData.GetNextExtraID();
                                AptCharacterBitmap b = new AptCharacterBitmap(image2, 256, 4, GlobalData, id);
                                GlobalData.AddExtraCharacter(b);
                                LinearStyles[linear.Gradient.GradientRecords] = id;
                            }
                            linear.BitmapID = (ushort)LinearStyles[linear.Gradient.GradientRecords];
                            break;
                        case RadialGradientFillStyleRGBA radial:
                            if (!RadialStyles.ContainsKey(radial.Gradient.GradientRecords))
                            {
                                byte[] image3 = MakeLinearGradient(radial.Gradient.GradientRecords);
                                ushort GradientCircleSize = 32;
                                byte[] image4 = MakeRadialGradientFromLinear(image3, GradientCircleSize);
                                int id = GlobalData.GetNextExtraID();
                                AptCharacterBitmap b = new AptCharacterBitmap(image4, GradientCircleSize, GradientCircleSize, GlobalData, id);
                                GlobalData.AddExtraCharacter(b);
                                RadialStyles[radial.Gradient.GradientRecords] = id;
                            }
                            radial.BitmapID = (ushort)RadialStyles[radial.Gradient.GradientRecords];
                            break;
                    }
                }
            }
        }

        public override void OutputCharacter(int i)
        {
            base.OutputCharacter(i);
            GlobalData.output.Write(3, (int)AptCharacterType.Shape);
            GlobalData.output.Write(3, 0x09876543);
            GlobalData.output.Write(3, BoundingRect);
            GlobalData.output.Write(3, i);
        }
        double[] MatInv(double[] matrix)
        {
            double[] mat = new double[6];
            double det = matrix[0] * matrix[3] - matrix[1] * matrix[2];
            mat[0] = matrix[3] / det;
            mat[1] = -matrix[1] / det;
            mat[2] = -matrix[2] / det;
            mat[3] = matrix[0] / det;
            mat[4] = -(mat[0] * matrix[4] + mat[2] * matrix[5]);
            mat[5] = -(mat[1] * matrix[4] + mat[3] * matrix[5]);
            return mat;
        }

        double[] MatMult(double[] m0, double[] m1)
        {
            double[] m = new double[16];
            for (int j = 0; j < 4; j++)
            {
                for (int i = 0; i < 4; i++)
                {
                    m[j * 4 + i] = m0[j * 4 + 0] * m1[0 * 4 + i] + m0[j * 4 + 1] * m1[1 * 4 + i] + m0[j * 4 + 2] * m1[2 * 4 + i] + m0[j * 4 + 3] * m1[3 * 4 + i];
                }
            }
            return m;
        }
        public string FormatColor(SwfRGBA color)
        {
            return @$"{color.Red}:{color.Green}:{color.Blue}:{color.Alpha}";
        }
        public void WriteShapeFile()
        {
            string filename = @$"{GlobalData.geometrydir}\{outid}.ru";
            using FileStream rus = new FileStream(filename, FileMode.Create);
            using StreamWriter ru = new StreamWriter(rus);
            if (shapes.Count == 0 || empty)
            {
                ru.Write("c\r\n");
                ru.Write("s s:0:0:0:0\r\n");
                ru.Write("t 0:0:0:0:0:0\r\n");
                return;
            }
            foreach (var ishape in shapes)
            {
                Dictionary<string, List<string>> tridata = new();
                List<string> trikeys = new();
                ru.Write("c\r\n");
                int tris = ishape.triangles.Count;
                if (tris > 0)
                {
                    foreach (var t in ishape.triangles)
                    {
                        var style = t.fill;
                        string tritext = @$"{(t.a.X / 20.0f)}:{(t.a.Y / 20.0f)}:{(t.b.X / 20.0f)}:{(t.b.Y / 20.0f)}:{(t.c.X / 20.0f)}:{(t.c.Y / 20.0f)}";
                        switch (style)
                        {
                            case SolidFillStyleRGBA solid:
                                {
                                    string key = "s:" + FormatColor(solid.Color);
                                    if (!tridata.ContainsKey(key))
                                    {
                                        trikeys.Add(key);
                                        tridata[key] = new();
                                    }
                                    tridata[key].Add(tritext);
                                }
                                break;
                            case LinearGradientFillStyleRGBA linear:
                                {
                                    double[] mat = new double[6];
                                    mat[0] = linear.GradientMatrix.ScaleX / 20.0f;
                                    mat[1] = linear.GradientMatrix.RotateSkew0 / 20.0f;
                                    mat[2] = linear.GradientMatrix.RotateSkew1 / 20.0f;
                                    mat[3] = linear.GradientMatrix.ScaleY / 20.0f;
                                    mat[4] = linear.GradientMatrix.TranslateX / 20.0f;
                                    mat[5] = linear.GradientMatrix.TranslateY / 20.0f;
                                    var invmat = MatInv(mat);
                                    double[] afmat = new double[16];
                                    afmat[0] = invmat[0];
                                    afmat[1] = invmat[1];
                                    afmat[2] = 0;
                                    afmat[3] = 0;
                                    afmat[4] = invmat[2];
                                    afmat[5] = invmat[3];
                                    afmat[6] = 0;
                                    afmat[7] = 0;
                                    afmat[8] = 0;
                                    afmat[9] = 0;
                                    afmat[10] = 1;
                                    afmat[11] = 0;
                                    afmat[12] = invmat[4];
                                    afmat[13] = invmat[5];
                                    afmat[14] = 0;
                                    afmat[15] = 1;
                                    double[] gradmat = new double[16];
                                    gradmat[0] = 256.0f / 32768.0f;
                                    gradmat[1] = 0;
                                    gradmat[2] = 0;
                                    gradmat[3] = 0;
                                    gradmat[4] = 0;
                                    gradmat[5] = 1.0f / 32768.0f;
                                    gradmat[6] = 0;
                                    gradmat[7] = 0;
                                    gradmat[8] = 0;
                                    gradmat[9] = 0;
                                    gradmat[10] = 1;
                                    gradmat[11] = 0;
                                    gradmat[12] = 0.5f * 256.0f;
                                    gradmat[13] = -0.5f;
                                    gradmat[14] = 0;
                                    gradmat[15] = 1;
                                    double[] m = MatMult(afmat, gradmat);
                                    if (m[0] == -0.0)
                                    {
                                        m[0] = 0.0;
                                    }
                                    if (m[1] == -0.0)
                                    {
                                        m[1] = 0.0;
                                    }
                                    if (m[4] == -0.0)
                                    {
                                        m[4] = 0.0;
                                    }
                                    if (m[5] == -0.0)
                                    {
                                        m[5] = 0.0;
                                    }
                                    if (m[12] == -0.0)
                                    {
                                        m[12] = 0.0;
                                    }
                                    if (m[13] == -0.0)
                                    {
                                        m[13] = 0.0;
                                    }
                                    FloatVector PackOffset = new FloatVector { X = 0, Y = 0 };
                                    if (GlobalData.AllCharacters[linear.BitmapID] is AptCharacterBitmap b)
                                    {
                                        PackOffset = b.PackOffset;
                                    }
                                    m[12] += PackOffset.X;
                                    m[13] += PackOffset.Y;
                                    string key = @$"tc:255:255:255:255:{linear.BitmapID}:{((float)m[0]).ToString("0.000000")}:{((float)m[1]).ToString("0.000000")}:{((float)m[4]).ToString("0.000000")}:{((float)m[5]).ToString("0.000000")}:{((float)m[12]).ToString("0.000000")}:{((float)m[13]).ToString("0.000000")}";
                                    if (!tridata.ContainsKey(key))
                                    {
                                        trikeys.Add(key);
                                        tridata[key] = new();
                                    }
                                    tridata[key].Add(tritext);
                                }
                                break;
                            case RadialGradientFillStyleRGBA radial:
                                {
                                    double[] mat = new double[6];
                                    mat[0] = radial.GradientMatrix.ScaleX / 20.0f;
                                    mat[1] = radial.GradientMatrix.RotateSkew0 / 20.0f;
                                    mat[2] = radial.GradientMatrix.RotateSkew1 / 20.0f;
                                    mat[3] = radial.GradientMatrix.ScaleY / 20.0f;
                                    mat[4] = radial.GradientMatrix.TranslateX / 20.0f;
                                    mat[5] = radial.GradientMatrix.TranslateY / 20.0f;
                                    var invmat = MatInv(mat);
                                    double[] afmat = new double[16];
                                    afmat[0] = invmat[0];
                                    afmat[1] = invmat[1];
                                    afmat[2] = 0;
                                    afmat[3] = 0;
                                    afmat[4] = invmat[2];
                                    afmat[5] = invmat[3];
                                    afmat[6] = 0;
                                    afmat[7] = 0;
                                    afmat[8] = 0;
                                    afmat[9] = 0;
                                    afmat[10] = 1;
                                    afmat[11] = 0;
                                    afmat[12] = invmat[4];
                                    afmat[13] = invmat[5];
                                    afmat[14] = 0;
                                    afmat[15] = 1;
                                    double[] gradmat = new double[16];
                                    ushort GradientCircleSize = 32;
                                    gradmat[0] = GradientCircleSize / 32768.0f;
                                    gradmat[1] = 0;
                                    gradmat[2] = 0;
                                    gradmat[3] = 0;
                                    gradmat[4] = 0;
                                    gradmat[5] = GradientCircleSize / 32768.0f;
                                    gradmat[6] = 0;
                                    gradmat[7] = 0;
                                    gradmat[8] = 0;
                                    gradmat[9] = 0;
                                    gradmat[10] = 1;
                                    gradmat[11] = 0;
                                    gradmat[12] = 0.5f * GradientCircleSize;
                                    gradmat[13] = 0.5f * GradientCircleSize;
                                    gradmat[14] = 0;
                                    gradmat[15] = 1;
                                    double[] m = MatMult(afmat, gradmat);
                                    if (m[0] == -0.0)
                                    {
                                        m[0] = 0.0;
                                    }
                                    if (m[1] == -0.0)
                                    {
                                        m[1] = 0.0;
                                    }
                                    if (m[4] == -0.0)
                                    {
                                        m[4] = 0.0;
                                    }
                                    if (m[5] == -0.0)
                                    {
                                        m[5] = 0.0;
                                    }
                                    if (m[12] == -0.0)
                                    {
                                        m[12] = 0.0;
                                    }
                                    if (m[13] == -0.0)
                                    {
                                        m[13] = 0.0;
                                    }
                                    FloatVector PackOffset = new FloatVector { X = 0, Y = 0 };
                                    if (GlobalData.AllCharacters[radial.BitmapID] is AptCharacterBitmap b)
                                    {
                                        PackOffset = b.PackOffset;
                                    }
                                    m[12] += PackOffset.X;
                                    m[13] += PackOffset.Y;
                                    string key = @$"tc:255:255:255:255:{radial.BitmapID}:{((float)m[0]).ToString("0.000000")}:{((float)m[1]).ToString("0.000000")}:{((float)m[4]).ToString("0.000000")}:{((float)m[5]).ToString("0.000000")}:{((float)m[12]).ToString("0.000000")}:{((float)m[13]).ToString("0.000000")}";
                                    if (!tridata.ContainsKey(key))
                                    {
                                        trikeys.Add(key);
                                        tridata[key] = new();
                                    }
                                    tridata[key].Add(tritext);
                                }
                                break;
                            case BitmapFillStyleRGBA bitmap:
                                {
                                    double[] mat = new double[6];
                                    mat[0] = bitmap.BitmapMatrix.ScaleX / 20.0f;
                                    mat[1] = bitmap.BitmapMatrix.RotateSkew0 / 20.0f;
                                    mat[2] = bitmap.BitmapMatrix.RotateSkew1 / 20.0f;
                                    mat[3] = bitmap.BitmapMatrix.ScaleY / 20.0f;
                                    mat[4] = bitmap.BitmapMatrix.TranslateX / 20.0f;
                                    mat[5] = bitmap.BitmapMatrix.TranslateY / 20.0f;
                                    var invmat = MatInv(mat);
                                    if (invmat[0] == -0.0)
                                    {
                                        invmat[0] = 0.0;
                                    }
                                    if (invmat[1] == -0.0)
                                    {
                                        invmat[1] = 0.0;
                                    }
                                    if (invmat[2] == -0.0)
                                    {
                                        invmat[2] = 0.0;
                                    }
                                    if (invmat[3] == -0.0)
                                    {
                                        invmat[3] = 0.0;
                                    }
                                    if (invmat[4] == -0.0)
                                    {
                                        invmat[4] = 0.0;
                                    }
                                    if (invmat[5] == -0.0)
                                    {
                                        invmat[5] = 0.0;
                                    }
                                    FloatVector PackOffset = new FloatVector { X = 0, Y = 0 };
                                    if (GlobalData.AllCharacters[bitmap.BitmapID] is AptCharacterBitmap b)
                                    {
                                        PackOffset = b.PackOffset;
                                    }
                                    invmat[4] += PackOffset.X;
                                    invmat[5] += PackOffset.Y;
                                    string key = @$"{((bitmap.Mode == BitmapMode.Repeat) ? "tw" : "tc")}:255:255:255:255:{bitmap.BitmapID}:{((float)invmat[0]).ToString("0.000000")}:{((float)invmat[1]).ToString("0.000000")}:{((float)invmat[2]).ToString("0.000000")}:{((float)invmat[3]).ToString("0.000000")}:{((float)invmat[4]).ToString("0.000000")}:{((float)invmat[5]).ToString("0.000000")}";
                                    if (!tridata.ContainsKey(key))
                                    {
                                        trikeys.Add(key);
                                        tridata[key] = new();
                                    }
                                    tridata[key].Add(tritext);
                                }
                                break;
                        }
                    }
                    foreach (var entry in trikeys)
                    {
                        ru.Write("s " + entry + "\r\n");
                        foreach (var t in tridata[entry])
                        {
                            ru.Write("t " + t + "\r\n");
                        }
                    }
                }
                int lines = ishape.lines.Count;
                if (lines > 0)
                {
                    Dictionary<string, List<string>> linedata = new();
                    List<string> linekeys = new();
                    foreach (var line in ishape.lines)
                    {
                        string key = "";
                        var style = line.style;
                        switch (style)
                        {
                            case LineStyleRGBA l:
                                {
                                    key = @$"l:{l.Width / 20.0f}:{FormatColor(l.Color)}";
                                }
                                break;
                        }
                        if (!linedata.ContainsKey(key))
                        {
                            linekeys.Add(key);
                            linedata[key] = new();
                        }
                        linedata[key].Add(@$"{(line.from.X / 20.0f)}:{(line.from.Y / 20.0f)}:{(line.to.X / 20.0f)}:{(line.to.Y / 20.0f)}");
                    }
                    foreach (var entry in linekeys)
                    {
                        ru.Write("s " + entry + "\r\n");
                        foreach (var t in linedata[entry])
                        {
                            ru.Write("l " + t + "\r\n");
                        }
                    }
                }
                if (lines == 0 && tris == 0)
                {
                    ru.Write("c\r\n");
                    ru.Write("s s:0:0:0:0\r\n");
                    ru.Write("t 0:0:0:0:0:0\r\n");
                    return;
                }
            }
            return;
        }

        public void UpdateShape(int i)
        {
            empty = true;
            if (!GlobalData.HitTestShapes.ContainsKey(i) || GlobalData.ReferencedCharacters.ContainsKey(i))
            {
                empty = false;
            }
            outid = i;
            if (shapes.Count == 0 || empty)
            {
                return;
            }
            foreach (var ishape in shapes)
            {
                int tris = ishape.triangles.Count;
                if (tris > 0)
                {
                    foreach (var t in ishape.triangles)
                    {
                        var style = t.fill;
                        switch (style)
                        {
                            case LinearGradientFillStyleRGBA linear:
                                {
                                    if (linear.GradientMatrix.HasRotate)
                                    {
                                        if (GlobalData.AllCharacters[linear.BitmapID] is AptCharacterBitmap b)
                                        {
                                            b.NoPack = true;
                                        }
                                    }
                                }
                                break;
                            case RadialGradientFillStyleRGBA radial:
                                {
                                    if (radial.GradientMatrix.HasRotate)
                                    {
                                        if (GlobalData.AllCharacters[radial.BitmapID] is AptCharacterBitmap b)
                                        {
                                            b.NoPack = true;
                                        }
                                    }
                                }
                                break;
                            case BitmapFillStyleRGBA bitmap:
                                {
                                    if (bitmap.BitmapMatrix.HasRotate)
                                    {
                                        if (GlobalData.AllCharacters[bitmap.BitmapID] is AptCharacterBitmap b)
                                        {
                                            b.NoPack = true;
                                        }
                                    }
                                }
                                break;
                        }
                    }
                }
            }
        }
        public AptCharacterShape(List<IShapeRecordRGB> shaperecs, List<FillStyleRGB> filllist, List<LineStyleRGB> linelist, Globals globaldata, int id) : base(globaldata, id)
        {
            BuildShapes(false, shaperecs, filllist, linelist);
        }

        public AptCharacterShape(List<IShapeRecordRGBA> shaperecs, List<FillStyleRGBA> filllist, List<LineStyleRGBA> linelist, Globals globaldata, int id) : base(globaldata, id)
        {
            BuildShapes(false, shaperecs, filllist, linelist);
        }

        public AptCharacterShape(List<IShapeRecordRGBA> shaperecs, List<FillStyleRGBA> filllist, List<LineStyleRGBA> linelist, int? line, int? fill0, int? fill1, Globals globaldata, int id) : base(globaldata, id)
        {
            BuildShapes(false, shaperecs, filllist, linelist, line, fill0, fill1);
        }

        public AptCharacterShape(DefineShapeTag tag, Globals globaldata) : base(globaldata, tag.TagID)
        {
            BoundingRect = new AptRect { fLeft = tag.ShapeBounds.XMin / 20.0f, fTop = tag.ShapeBounds.YMin / 20.0f, fRight = tag.ShapeBounds.XMax / 20.0f, fBottom = tag.ShapeBounds.YMax / 20.0f };
            BuildShapes(false, tag.ShapeRecords, tag.FillStyles, tag.LineStyles);
        }
        public AptCharacterShape(DefineShape2Tag tag, Globals globaldata) : base(globaldata, tag.TagID)
        {
            BoundingRect = new AptRect { fLeft = tag.ShapeBounds.XMin / 20.0f, fTop = tag.ShapeBounds.YMin / 20.0f, fRight = tag.ShapeBounds.XMax / 20.0f, fBottom = tag.ShapeBounds.YMax / 20.0f };
            BuildShapes(true, tag.ShapeRecords, tag.FillStyles, tag.LineStyles);
        }
        public AptCharacterShape(DefineShape3Tag tag, Globals globaldata) : base(globaldata, tag.TagID)
        {
            BoundingRect = new AptRect { fLeft = tag.ShapeBounds.XMin / 20.0f, fTop = tag.ShapeBounds.YMin / 20.0f, fRight = tag.ShapeBounds.XMax / 20.0f, fBottom = tag.ShapeBounds.YMax / 20.0f };
            BuildShapes(true, tag.ShapeRecords, tag.FillStyles, tag.LineStyles);
        }
    }
}