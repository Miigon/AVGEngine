package ResBuilder;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class ResBuilder 
{
	private static List<File> fileList = new ArrayList<File>();
	
	private static void enumFile(File file)
	{
		File flist[] = file.listFiles();
		
		if (flist == null || flist.length == 0) 
			return;
		 
		for (File f : flist) {  
			if (f.isDirectory()) 
			{  
				System.out.println("Found dir===>" + f.getAbsolutePath());   
				enumFile(f);  
			} 
			else 
			{  
				System.out.println("Dound file==>" + f.getAbsolutePath());
				fileList.add(f.getAbsoluteFile());
			}  
		}  
	} 
	
	public static void main(String[] args) throws IOException
	{
		String resPath;
		if (args.length < 2)
		{
			System.out.print("ResBuilder.jar [Res Path] [out]\n");
			return;
		}
		else
			resPath = args[0];
		
		File baseFile = new File(resPath);
		
		enumFile(baseFile);
		
		System.out.print("Creating package...\n");
		System.out.print("Package dir: " + baseFile.getAbsolutePath() + "\n");
		
		/* Pack File:
		 * |Pack Head|Package GUID|File Name|File Size(string)|File Data|File Name......l..
		 *     PK         GUID        name       a string        ....
		 */
		File resPackage = new File(args[1]);
		
		//create file
		if (!resPackage.exists())
			resPackage.createNewFile();
		
		FileOutputStream fs = new FileOutputStream(resPackage);
		
		//head
		fs.write('P');
		fs.write('K');
		
		//version
		fs.write(java.util.UUID.randomUUID().toString().getBytes());
		
		for (File file : fileList)
		{
			//file name
			String resName = file.getAbsolutePath().substring(baseFile.getAbsolutePath().length() + 1).replace('\\','/');
			
			fs.write(resName.getBytes());
			fs.write('\0');
			
			//size
			String fileSize = Long.toString(file.length());
			fs.write(fileSize.getBytes());
			fs.write('\0');
			
			System.out.print("Add size " + fileSize + " \t\tRes name " + resName + "\n");

			//file data
			byte[] fileByte = new byte[1];
			FileInputStream inFile = new FileInputStream(file);
			while (inFile.read(fileByte) != -1)
				fs.write(fileByte);
			
			inFile.close();
		}
		
		fs.close();
	}
}
