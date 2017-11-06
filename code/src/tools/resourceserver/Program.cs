using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace tools.unittestgenerator
{
    public partial class UnitTest
    {
        public UnitTest(string projectName)
        {
            Name = projectName;
        }

        public string Name;
    }
    class Program
    {
        static public string FindProjectRoot(string path)
        {
            DirectoryInfo directory = new DirectoryInfo(path);
            string root = directory.FullName;
            while (directory.Parent != null && directory.Parent.Name != "engine")
            {
                directory = directory.Parent;
            }

            root = directory.Parent.FullName;

            return root;
        }

        static void Main(string[] args)
        {
            if (args.Length != 1)
            {
                ShowUsage();
                return;
            }

            Console.Write("Creating unit test for {0}", args[0]);

            var fullPath = Path.GetFullPath(args[0]);

            Console.Write("Creating unit test for {0}", fullPath);

            var projectPath = args[0];
            var outputPath = Path.Combine(fullPath, "_unittest\\test.cpp");

            if (File.Exists(outputPath))
            {
                Console.WriteLine("Unit test already exists at {0}, generation will be skipped to prevent overwriting the unit test", outputPath);
                //return;
            }

            var projectName = Path.GetFileNameWithoutExtension(projectPath);
            var directoryName = new FileInfo(outputPath).Directory.FullName;
            if (Directory.Exists(directoryName) == false)
            {
                Directory.CreateDirectory(directoryName);
            }

            var generator = new UnitTest(projectName);
            var text = generator.TransformText();
            File.WriteAllText(outputPath, text);

            var sourcePath = Path.GetFullPath("./copyfiles");
            Console.WriteLine("Copying files from {0} to {1}", sourcePath, directoryName);
            string[] files = System.IO.Directory.GetFiles(sourcePath);

            // Copy the files and overwrite destination files if they already exist.
            foreach (string s in files)
            {
                // Use static Path methods to extract only the file name from the path.
                var fileName = System.IO.Path.GetFileName(s);
                var destFile = System.IO.Path.Combine(directoryName, fileName);
                System.IO.File.Copy(s, destFile, false);
            }
        }

        static private void ShowUsage()
        {
            Console.WriteLine("Usage: unittestgenerator.exe -projectPath");
        }
    }
}
