using System;

namespace EngineEditor
{
    /*
    In questa classe i Point3 rappresentano le informazioni riguardo a un singolo vertice del triangolo:
        x: ID della posizione del vetice nello spazio
        y: ID della coordinata UV
        z: ID della normale
    */

    /// <summary>
    /// Struct che rappresenta una faccia di un triangolo tramite gli ID di vertici, UV e normali
    /// </summary>
    public class TriangleFace
    {
        Point3[] verteces = new Point3[3];

        /// <summary>
        /// Ottiene il primo vertice della faccia del triangolo
        /// </summary>
        public Point3 V1
        {
            get { return verteces[0]; }
            set { verteces[0] = value; }
        }

        /// <summary>
        /// Ottiene il secondo vertice della faccia del triangolo
        /// </summary>
        public Point3 V2
        {
            get { return verteces[1]; }
            set { verteces[1] = value; }
        }

        /// <summary>
        /// Ottiene il terzo vertice della faccia del triangolo
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
        /// Ottiene o imposta i parametri per il vertice desiderato
        /// </summary>
        /// <param name="VertexIndex">Indice compreso tra 0 e 2</param>
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
