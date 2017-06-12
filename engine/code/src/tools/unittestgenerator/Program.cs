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
            //
            // test 
            args = new string[1];
            args[0] = "C:\\dev\\game\\engine\\code\\src\\system\\base";

            var fullPath = Path.GetFullPath(args[0]);

            //

            if (args.Length != 1)
            {
                ShowUsage();
                return;
            }
            var projectPath = args[0];
            var outputPath = Path.Combine(fullPath, "_unittest\\test.cpp");

            if(File.Exists(outputPath))
            {
                Console.WriteLine("Unit test already exists at {0}, generation will be skipped to prevent overwriting the unit test", outputPath);
                //return;
            }

            var projectName = Path.GetFileNameWithoutExtension(projectPath);
            var directoryName = new FileInfo(outputPath).Directory.FullName;
            if(Directory.Exists(directoryName) == false)
            {
                Directory.CreateDirectory(directoryName);
            }

            var generator = new UnitTest(projectName);
            var text = generator.TransformText();
            File.WriteAllText(outputPath, text);
        }

        static private void ShowUsage()
        {
            Console.WriteLine("Usage: unittestgenerator.exe -projectPath");
        }
    }
}
