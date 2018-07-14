using System;

namespace EngineEditor
{
    /*
    In this class, Point3 represent information about a single vertex of the triangle:
         x: ID of the position of the vetice in the space
         y: ID of the UV coordinate
         z: ID of the normal
    */

    /// <summary>
    /// Struct that represents a face of a triangle using vertex, UV, and normal IDs
    /// </summary>
    public class TriangleFace
    {
        Point3[] verteces = new Point3[3];

        /// <summary>
        /// Gets the first vertex of the triangle face
        /// </summary>
        public Point3 V1
        {
            get { return verteces[0]; }
            set { verteces[0] = value; }
        }

        /// <summary>
        /// Gets the second vertex of the triangle face
        /// </summary>
        public Point3 V2
        {
            get { return verteces[1]; }
            set { verteces[1] = value; }
        }

        /// <summary>
        /// Gets the third vertex of the face of the triangle
        /// </summary>
        public Point3 V3
        {
            get { return verteces[2]; }
            set { verteces[2] = value; }
        }




        public TriangleFace()
        { }

        public TriangleFace(Point3 V1, Point3 V2, Point3 V3)
        {
            this.V1 = V1;
            this.V2 = V2;
            this.V3 = V3;
        }

        /// <summary>
        /// Gets or sets the parameters for the desired vertex
        /// </summary>
        /// <param name="VertexIndex">Index between 0 and 2</param>
        public Point3 this[int VertexIndex]
        {
            get
            {
                if (VertexIndex >= 0 || VertexIndex < 3)
                    return verteces[VertexIndex];
                else
                    throw new ArgumentException("VertexIndex not valid: " + VertexIndex);
            }

            set
            {
                if (VertexIndex >= 0 || VertexIndex < 3)
                    verteces[VertexIndex] = value;
                else
                    throw new ArgumentException("VertexIndex not valid: " + VertexIndex);
            }
        }
    }
}
