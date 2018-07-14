using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;

namespace EngineEditor
{
    /// <summary>
    /// Static class that provides conversion methods for assets
    /// </summary>
    public static class AssetConverter
    {
        /// <summary>
        /// Convert an OBJ file to MSH
        /// </summary>
        /// <param name="PathOBJ">Path to the file in OBJ format</param>
        /// <param name="PathMSH">Path to the file to be created MSH</param>
        public static void ConvertOBJToMSH(string PathOBJ, string PathMSH)
        {
            List<Vec3> vertecesIDs = new List<Vec3>();
            List<Vec2> uvsIDs = new List<Vec2>();
            List<Vec3> normalsIDs = new List<Vec3>();
            List<TriangleFace> faces = new List<TriangleFace>();

            LoadOBJ(vertecesIDs, uvsIDs, normalsIDs, faces, PathOBJ);
            SaveFileMSH(PathMSH, vertecesIDs, uvsIDs, normalsIDs, faces);
        }


        /// <summary>
        /// Upload an OBJ file
        /// </summary>
        /// <param name="Verteces">List of vertices present in the mesh (not null)</param>
        /// <param name="UVs">UV present in the mesh (not null)</param>
        /// <param name="Normals">Normal present in the face (not nothing)</param>
        /// <param name="Faces">Faces that make up the mesh (not anything)</param>
        /// <param name="Path">Path to the .obj file</param>
        private static void LoadOBJ(List<Vec3> Verteces, List<Vec2> UVs, List<Vec3> Normals, List<TriangleFace> Faces, string Path)
        {
            if (!File.Exists(Path))
                throw new FileNotFoundException("Path: " + Path);

            StreamReader sr = new StreamReader(Path);

            while (!sr.EndOfStream)
            {
                string line = sr.ReadLine();
                string[] v = line.Split(' ');

                if(v.Length > 0)
                {
                    string initial = v[0];
                    if(initial == "v") // Case is a summit
                    {
                        Verteces.Add(Vec3FromString(v[1], v[2], v[3]));
                    }
                    else if(initial == "vt") // case is a UV
                    {
                        UVs.Add(Vec2FromString(v[1], v[2]));
                    }
                    else if(initial == "vn") // case is a normal one
                    {
                        Normals.Add(Vec3FromString(v[1], v[2], v[3]));
                    }
                    else if(initial == "f") // Case is a face
                    {
                        Faces.Add(LoadTriangleFace(v));
                    }
                }
            }


            sr.Close();
        }

        /// <summary>
        /// Converts the array of strings to a face and the face of the triangle
        /// </summary>
        /// <param name="S">Array obtained by splitting the space character string of the face line of the OBJ file</param>
        private static TriangleFace LoadTriangleFace(string[] S)
        {
            TriangleFace tr = new TriangleFace();

            for(int i = 1; i < 4; i++) // Cycle for the 3 vertices of the triangle
            {
                string[] singleVertexDataString = S[i].Split('/'); // I take the data associated with the summit
                Point3 singleVertexData = new Point3(); // Representation of the single summit

                if (singleVertexDataString.Length == 3)
                {
                    singleVertexData.x = Convert.ToInt32(singleVertexDataString[0]);
                    if (singleVertexDataString[1] == "")
                        throw new Exception(".OBJ without UVs");
                    else
                        singleVertexData.y = Convert.ToInt32(singleVertexDataString[1]);
                    singleVertexData.z = Convert.ToInt32(singleVertexDataString[2]);
                }
                else if (singleVertexDataString.Length == 2)
                {
                    singleVertexData.x = Convert.ToInt32(singleVertexDataString[0]);
                    singleVertexData.y = Convert.ToInt32(singleVertexDataString[1]);
                }

                tr[i - 1] = singleVertexData;
            }

            return tr;
        }


        private static void SaveFileMSH(string Path, List<Vec3> Verteces, List<Vec2> UVs, List<Vec3> Normals, List<TriangleFace> Faces)
        {
            FileStream fs = new FileStream(Path, FileMode.Create);
            BinaryWriter bw = new BinaryWriter(fs);

            bw.Write(new char[] { 'M', 'S', 'H' }); // I write the header
            bool normals = Normals.Count > 0;
            if (normals) // Flags for the presence of normal
                bw.Write((byte)0x01); // present
            else
                bw.Write((byte)0x0); // Not present

            // Except for the size of the Box
            float minX, minY, minZ, maxX, maxY, maxZ;
            BoundsMesh(out maxX, out minX, out maxY, out minY, out maxZ, out minZ, Verteces);
            bw.Write(maxX);
            bw.Write(minX);
            bw.Write(maxY);
            bw.Write(minY);
            bw.Write(maxZ);
            bw.Write(minZ);

            // Vertices
            bw.Write(Verteces.Count);
            for(int i = 0; i < Verteces.Count; i++)
            {
                bw.Write(Verteces[i].x);
                bw.Write(Verteces[i].y);
                bw.Write(Verteces[i].z);
            }

            // UV
            bw.Write(UVs.Count);
            for (int i = 0; i < UVs.Count; i++)
            {
                bw.Write(UVs[i].x);
                bw.Write(UVs[i].y);
            }

            // Normal (if any)
            if (normals)
            {
                bw.Write(Normals.Count);
                for (int i = 0; i < Normals.Count; i++)
                {
                    bw.Write(Normals[i].x);
                    bw.Write(Normals[i].y);
                    bw.Write(Normals[i].z);
                }
            }

            // Faces
            const int NUM_VERTECES_TRIANGLE = 3;
            bw.Write(Faces.Count);
            for (int i = 0; i < Faces.Count; i++)
                for (int j = 0; j < NUM_VERTECES_TRIANGLE; j++)
                    SaveVertexFace(Faces[i][j], normals, bw);



            bw.Close();
            fs.Close();
        }

        private static void SaveVertexFace(Point3 V, bool normals, BinaryWriter bw)
        {
            bw.Write(V.x);
            bw.Write(V.y);
            if(normals)
                bw.Write(V.z);
        }

        /// <summary>
        /// Return the limits of the mesh
        /// </summary>
        /// <param name="Verteces">Mesh vertices (at least 1 dimension)</param>
        private static void BoundsMesh(out float MaxX, out float MinX, out float MaxY, out float MinY, out float MaxZ, out float MinZ, List<Vec3> Verteces)
        {
            MaxX = Verteces[0].x;
            MinX = Verteces[0].x;
            MaxY = Verteces[0].y;
            MinY = Verteces[0].y;
            MaxZ = Verteces[0].z;
            MinZ = Verteces[0].z;
            for (int i = 1; i < Verteces.Count; i++)
            {
                MaxX = Math.Max(MaxX, Verteces[i].x);
                MaxY = Math.Max(MaxY, Verteces[i].y);
                MaxZ = Math.Max(MaxZ, Verteces[i].z);
                MinX = Math.Min(MinX, Verteces[i].x);
                MinY = Math.Min(MinY, Verteces[i].y);
                MinZ = Math.Min(MinZ, Verteces[i].z);
            }
        }


        private static Vec3 Vec3FromString(string X, string Y, string Z)
        {
            return new Vec3(
                Convert.ToSingle(X, CultureInfo.InvariantCulture), 
                Convert.ToSingle(Y, CultureInfo.InvariantCulture), 
                Convert.ToSingle(Z, CultureInfo.InvariantCulture)
            );
        }

        private static Vec2 Vec2FromString(string X, string Y)
        {
            return new Vec2(
                Convert.ToSingle(X, CultureInfo.InvariantCulture), 
                Convert.ToSingle(Y, CultureInfo.InvariantCulture)
            );
        }
    }
}
