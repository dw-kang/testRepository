using Microsoft.WindowsAPICodePack.Dialogs;
using System;
using System.Collections.Generic;
using System.IO;
using System.Security.Cryptography;
using System.Text;
using System.Windows;
using System.Windows.Controls;

namespace ImageDirDiff
{
    /// <summary>
    /// MainWindow.xaml에 대한 상호 작용 논리
    /// </summary>
    public partial class MainWindow : Window
    {
        struct FilesInfo
        {
            public string filePath;
            public long fileSize;
        }

        List<FilesInfo> file1List = null;
        List<FilesInfo> file2List = null;

        public MainWindow()
        {
            WindowStartupLocation = System.Windows.WindowStartupLocation.CenterScreen;

            InitializeComponent();

            file1List = new List<FilesInfo>();
            file2List = new List<FilesInfo>();
        }

        private void DirSelectButton1_Click(object sender, RoutedEventArgs e)
        {
            OpenFileDlg(sender);
        }

        private void DirSelectButton2_Click(object sender, RoutedEventArgs e)
        {
            OpenFileDlg(sender);
        }

        private void OutputDirSelectButton_Click(object sender, RoutedEventArgs e)
        {
            OpenFileDlg(sender);
        }

        /// <summary>
        ///  버튼 클릭시 다이얼로그를 열고 유효하면 레이블에 반영
        /// </summary>
        /// <returns></returns>
        private void OpenFileDlg(object sender)
        {
            // 다이얼로그 설정
            var dlg = new CommonOpenFileDialog();
            dlg.Title = "Title";
            dlg.IsFolderPicker = true;
            dlg.InitialDirectory = Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments);
            dlg.AddToMostRecentlyUsedList = false;
            dlg.AllowNonFileSystemItems = false;
            dlg.DefaultDirectory = Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments);
            dlg.EnsureFileExists = true;
            dlg.EnsurePathExists = true;
            dlg.EnsureReadOnly = false;
            dlg.EnsureValidNames = true;
            dlg.Multiselect = false;
            dlg.ShowPlacesList = true;

            // 버튼
            Button sendedButton = (Button)sender;

            if (dlg.ShowDialog() == CommonFileDialogResult.Ok)
            {
                if (Directory.Exists(dlg.FileName))
                {
                    if (sendedButton.Name == "dirSelectButton1")
                    {
                        selectedPath1.Content = dlg.FileName;

                        string[] selectedPath1Files = Directory.GetFiles(selectedPath1.Content.ToString(), "*.*", SearchOption.AllDirectories);

                        foreach (string file1 in selectedPath1Files)
                        {
                            FilesInfo tmpFilesInfo;
                            tmpFilesInfo.filePath = file1;
                            tmpFilesInfo.fileSize = new System.IO.FileInfo(file1).Length;
                            file1List.Add(tmpFilesInfo);
                        }
                    }
                    else if (sendedButton.Name == "dirSelectButton2")
                    {
                        selectedPath2.Content = dlg.FileName;

                        string[] selectedPath2Files = Directory.GetFiles(selectedPath2.Content.ToString(), "*.*", SearchOption.AllDirectories);

                        foreach (string file2 in selectedPath2Files)
                        {
                            FilesInfo tmpFilesInfo;
                            tmpFilesInfo.filePath = file2;
                            tmpFilesInfo.fileSize = new System.IO.FileInfo(file2).Length;
                            file2List.Add(tmpFilesInfo);
                        }
                    }
                    else if (sendedButton.Name == "outputDirSelectButton")
                    {
                        outputDirectoryPath.Content = dlg.FileName;
                    }
                }
            }
        }

        private void StartButton_Click(object sender, RoutedEventArgs e)
        {
            int equalcount = 0;
            int diffrentcount = 0;
            StringBuilder diffstring = new StringBuilder();

            foreach (FilesInfo file1 in file1List)
            {
                bool founded = false;

                foreach (FilesInfo file2 in file2List)
                {
                    if (file1.fileSize == file2.fileSize)
                    {
                        string file1hash = "";
                        string file2hash = "";

                        using (var md5 = MD5.Create())
                        {
                            using (var stream = File.OpenRead(file1.filePath))
                            {
                                md5.ComputeHash(stream);
                                file1hash = BitConverter.ToString(md5.ComputeHash(stream)).Replace("-", "");
                            }

                            using (var stream = File.OpenRead(file2.filePath))
                            {
                                md5.ComputeHash(stream);
                                file2hash = BitConverter.ToString(md5.ComputeHash(stream)).Replace("-", "");
                            }

                            if (String.CompareOrdinal(file1hash, file2hash) == 0)
                            {
                                outputText.Inlines.Add(file1.filePath + ", " + file2.filePath + "\n");
                                equalcount++;
                                founded = true;
                            }
                        }
                    }
                }

                if(founded == false)
                {
                    diffstring.AppendLine(file1.filePath);
                }
            }

            diffrentcount = file1List.Count - equalcount;

            MessageBox.Show("Equal count : " + equalcount.ToString() + "\ndir1 - dir2 diffrent count : " + diffrentcount.ToString() + "\n" + diffstring.ToString());
        }
    }
}
