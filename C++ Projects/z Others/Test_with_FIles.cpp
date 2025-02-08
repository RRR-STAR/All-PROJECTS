#include <iostream>
#include <conio.h>
#include <fstream>
#include <iomanip>
using namespace std;

  /* open a file Write in it and read the Written Data and shows it on console */

// main(){
//   ofstream  file_write;
//   file_write.open("D:\\OneDrive\\Desktop\\example.txt");

//   cout <<endl<<" Enter Data to Write in File >\n and when Complete Press Enter <-|\n : ";
//   for (char  c = ws(cin).get(); c != '\n'; cin.get(c)){
//     file_write << c;
//   }

//   cout <<endl<<" Operation Completed. Data written in File.";
//   // file_write.close();

//   if (file_write.is_open() == true){
//     cout <<endl<<" File Already Opened ! ";
//     file_write.close();
//     ifstream  file_read;
//     file_read.open("D:\\OneDrive\\Desktop\\example.txt");

//     char  *data_in_file = new char[300];
//     cout <<endl<<endl<<" Content of the File : ";
//     file_read.getline(data_in_file, 300);
//     cout <<endl<<"    "<< data_in_file;

//     delete []data_in_file;
//     file_read.close();
//     cout <<endl<<" File Closed after reading Data through 1 method !";
//   } 
//   else {
//     cout <<endl<<" File Opened !";
//     ifstream  file_read;
//     file_read.open("D:\\OneDrive\\Desktop\\example.txt");

//     char  *data_in_file = new char[300];
//     cout <<endl<<endl<<" Content of the File : ";
//     file_read.getline(data_in_file, 300);
//     cout <<endl<<"    "<< data_in_file;

//     delete []data_in_file;
//     file_read.close();
//     cout <<endl<<" File Closed after reading Data through 2 method !";
//   }
//   getch();  return 0;
// }

  /* open a existed file and read data from it and shows it in console */

// main(){
//   ifstream  file_read;
//   file_read.open("D:\\OneDrive\\Desktop\\R.txt");

//   if (file_read.is_open()){ cout <<endl<<" File Opened ! "<<endl; }
//   else { cout <<endl<<" Error ! in File Opening ."<<endl;  exit(0); }
//   cout <<endl<<" Data Available in R.txt "<<endl;

//   while (file_read){ // this loop will end when the EOF encountered ~!
//     char  *data_in_R_txtFile = new char[500];
//     file_read.getline(data_in_R_txtFile, 500);
//     cout <<endl<< data_in_R_txtFile;
//     delete []data_in_R_txtFile;
//   }
//   file_read.close();
//   return 0;
// }

  /* Open two Existed Files and Write in it from another File (do copy) */

// main(){
//   ifstream  file_read;
//   ofstream  file_write;

//   file_read.open("D:\\OneDrive\\Desktop\\R.txt");

//   if (file_read.is_open() == true){ cout <<endl<<" File Opened ! "; }
//   else { cout <<endl<<" Error in File Opening ! \n\n";  exit(0); }

//   file_write.open("D:\\OneDrive\\Desktop\\z.txt");

//   cout <<endl<<" Data transfering start ... ";
//   while (file_read.eof() != true){
//     char  *data_in_file_Rtxt = new char[500];

//     file_read.getline(data_in_file_Rtxt, 500);
//     file_write <<endl<< data_in_file_Rtxt;

//     delete []data_in_file_Rtxt;
//   }
//   file_read.close();  file_write.close();
//   cout <<endl<<" Data Successfully Transfered !";

//   getch();  return 0;
// }

  /* Different Modes of Files Opening */

// main(){
//   // open a mode to there from where it left by ios::app
//   ofstream  file_write;
//   file_write.open("D:\\OneDrive\\Desktop\\z.txt", ios :: app);

//   if (file_write.is_open()){ cout <<endl<<" File Opened ."; }
//   else { cout <<endl<<" Error in File Opening !";  exit(0); }

//   file_write <<endl<<" This is a New Text which is Appened here !";
//   cout <<endl<<" New Data is added to End of the File !";
//   file_write.close();

//   ifstream  file_read;
//   file_read.open("D:\\OneDrive\\Desktop\\z.txt", ios :: in);

//   if (file_read.is_open()){ cout <<endl<<" File Reading start ... "; }
//   else { cout <<endl<<" Error in File Reading !";  exit(0); }

//   cout <<endl<<" Data in File > "<<endl;
//   for (char  *data_in_file = new char[100]; file_read.eof() != true; data_in_file = new char[100]){
//     file_read.getline(data_in_file, 100);
//     cout <<endl<< data_in_file;
//     delete  data_in_file;
//   }
//   file_read.close();

//   getch();  return 0;
// }

  /* Re-positing & get the File pointers */

// main(){
//   ofstream  file_write("D:\\OneDrive\\Desktop\\z2.txt");

//   file_write <<" File Line 1 Statement .";
//   file_write <<endl<<" File Line 2 Statement .";
//   file_write <<endl<<" File Line 3 Statement ."<<endl;

//   // store the current position and re-position the File output Pointer
//   int  out_ptr_cur_pos = file_write.tellp();
//   file_write.seekp(0, ios::beg);
//   file_write <<" File Line 4 Statement .";

//   // again reposition the output pointer
//   file_write.seekp(out_ptr_cur_pos, ios::beg);
//   file_write <<" File Line 5 Statement .";

//   cout <<endl<<" File Written successful and File closed !";
//   cout <<endl<<" File op Pointer Loc : "<< file_write.tellp();
//   file_write.close();

//   // Now read the File Data by Input Pointer 
//   ifstream  file_read("D:\\OneDrive\\Desktop\\z2.txt");
//   cout <<endl<<" Data in File > "<<endl;

//   cout <<endl<<" File ip Pointer Loc : "<< file_read.tellg();
//   cout <<endl<<" File eof : "<< file_read.eof();

//   // read the first two lines
//     char  *data_in_file = new char[30];
//     file_read.getline(data_in_file, 30);
//     cout <<endl<< data_in_file;
//     file_read.getline(data_in_file, 30);
//     cout <<endl<< data_in_file;
//     delete []data_in_file;

//   // store the current pos of input pointer and reposition it
//   int  in_ptr_cur_pos = file_read.tellg();
//   cout <<endl<<" File ip Pointer Loc : "<< file_read.tellg();
//   cout <<endl<<" File eof : "<< file_read.eof();
//   file_read.seekg(0, ios::beg);
//   cout <<endl<<" File ip Pointer Loc : "<< file_read.tellg();

//   // again read from the first
//   while (file_read.eof() != true){
//     char  *data_in_file = new char[30];
//     file_read.getline(data_in_file, 30);
//     cout <<endl<< data_in_file;
//     delete []data_in_file;
//   }

//   cout <<endl<<" File ip Pointer Loc : "<< file_read.tellg();
//   cout <<endl<<" File eof : "<< file_read.eof();

//   getch();  return 0;
// }



  /* Read & Write Data into File by specific read() & write() function of File */

// class CitiesAndCodes {
//   char  *city_name;
//   unsigned int  city_code;
//   public :
//   void getCityData(){
//     city_name = new char[30];
//     cout <<endl<<" Enter City Name : ";
//     ws(cin).getline(city_name, 30);
//     cout <<" Enter City Code : ";
//     cin >> city_code;
//   }
//   void putCityData(){
//     cout <<endl<<"\tCity Name : "<< city_name;
//     cout <<endl<<"\tCity Code : "<< city_code;
//     delete []city_name;
//   }
// };
// main(){
//   CitiesAndCodes  *obj1 = new CitiesAndCodes, *obj2 = new CitiesAndCodes;
//   obj1->getCityData();

//   fstream  file_f;
//   file_f.open("D:\\OneDrive\\Desktop\\z.txt", ios::trunc | ios::out | ios::in);

//   // write the Data into File through obj(obj1)
//   file_f.write((char *) &obj1, sizeof(obj1));

//   cout <<endl<<" Data Written in File !"<<endl;

//   // re-position file ip Pointer 
//   //read the Data from File into another obj(obj2)
//   file_f.seekg(0, ios::beg);
//   file_f.read((char *) &obj2, sizeof(obj2));

//   // shows the Data through another obj
//   cout <<endl<<" Data in File > "<<endl;
//   obj2->putCityData();

//   file_f.close();
//   delete obj1;  delete obj2;

//   getch();  return 0;
// }

  /* Difference between Normal array and Class data member array  */

// class Arr {
//   private :
//   int  arr[5];
//   public :
//   void intilizeAll(){
//     for (int  i = 0; i < 5; i++){
//       arr[i] = 10 + i;
//     }
//   }
//   void setZeroToAll(){
//     for (int  i = 0; i < 5; i++){
//       arr[i] = 0;
//     }
//   }
//   void displayAll(){
//     cout <<endl<<" Class arr Elements : ";
//     for (int  i = 0; i < 5; i++){
//       cout <<setw(5)<< arr[i];
//     }
//   }
// };
// main(){
//   float  arr1[5] = {20, 21, 22, 23, 24}, arr2[5];
//   Arr  *obj1 = new Arr, *obj2 = new Arr;
//   obj1->intilizeAll();

//   // write Data in the Files
//   ofstream  file_write;

//   file_write.open("D:\\OneDrive\\Desktop\\z.txt");
//   file_write.write((char *) &obj1, sizeof(obj1));
//   file_write.close();

//   file_write.open("D:\\OneDrive\\Desktop\\z2.txt");
//   file_write.write((char *) &arr1, sizeof(arr1));
//   file_write.close();

//   // set obj1 arr & normal arr elems to Zero
//   obj1->setZeroToAll();
//   for (int  i = 0; i < 5; i++){ arr1[i] = 0; }

//   // read Data from Files and Display
//   ifstream  file_read;

//   file_read.open("D:\\OneDrive\\Desktop\\z.txt");
//   file_read.read((char *) &obj2, sizeof(obj2));
//   obj2->displayAll();
//   file_read.close();

//   file_read.open("D:\\OneDrive\\Desktop\\z2.txt");
//   file_read.read((char *) &arr2, sizeof(arr2));
//   for (int  i = 0; i < 5; i++){ cout <<endl<< arr2[i]; }
//   file_read.close();

//   getch();  return 0;
// }

  /* Re-open , Add , Modify file Data */

class Cities {
  char  *city_name;
  unsigned int  city_code;
  
  public :
  
  Cities(){}
  ~Cities(){ delete []city_name; }
  
  void getData(){
    city_name = new char[50];
    cout <<endl<<" Enter the City Name : ";
    ws(cin).getline(city_name, 50);
    cout <<" Enter City Code : ";
    cin >> city_code;
  }
  void putData(){
    cout <<endl<<endl<<"\t City Name : "<< city_name;
    cout <<endl<<"\t City Code : "<< city_code <<endl;
  }
};


main(){
  Cities  *obj = new Cities();
  
  // we can also create a pointer to File Streams like obj's
  ofstream  *file_write = new ofstream("D:\\OneDrive\\Desktop\\z.txt", ios::out);
  
  // put some data as a existed content
  for (int  i = 0; i != 3; i++){
    obj->getData();
    file_write->write((char *) obj, sizeof(*obj));
  } 
  file_write->close();
  delete file_write;
  
  // now read the content assuming as a existed content
  fstream  file_f("D:\\OneDrive\\Desktop\\z.txt", ios::ate | ios::in | ios::out | ios::binary);
  
  if (file_f.is_open() != true){ 
    cout <<endl<<" Error in File opening ! ";  
    file_f.close();  exit(0); 
  }
  cout <<endl<<" EXISTED CONTENT OF THE FILE "<<endl;
  file_f.seekg(0, ios::beg);
  
  while (file_f.read((char *) obj, sizeof(*obj))){
    obj->putData();
  }
  file_f.clear();// turn of the EOF [it is needed to read & display the Updated Output from Binary Format]
  cout <<endl<<" current EOF = "<< file_f.eof();
  
  // Add a new City in File Content [and as we know that the current file pointer is pointed at last at this time , that's why simply we add it in the File]
  cout <<endl<<" Enter data to Add a New City ";  
  obj->getData();
  
  file_f.write((char *) obj, sizeof(*obj));
  
  // now see the Updated data of the File
  cout <<endl<<" FILE CONTENT AFTER ADD NEW DATA "<<endl;
  file_f.seekg(0, ios::beg);
  
  while (file_f.read((char *) obj, sizeof(*obj))){
    obj->putData();
  }
  // Now find the Number of Total Objects(Cities)
  file_f.clear();// again turn-off all the flags and reset the pointers
  int  no_of_obj, cur_eof_loc = file_f.tellp();
  
  /* [ All obj's size / single obj size = No. of obj's ] */
  no_of_obj = cur_eof_loc / sizeof(*obj);
  
  cout <<endl<<" Total Bytes in File or Size of all Cities : "<< cur_eof_loc;
  cout <<endl<<" No. of Cities Present : "<< no_of_obj <<endl;
  
  // Now Modify an Object data
  int  obj_no, obj_loc;  $_WrongInput :
  cout <<endl<<" Enter City No. to Update : ";  cin >> obj_no;
  
  if (obj_no <= 0 || obj_no > no_of_obj){ 
    cout <<endl<<" There are only "<< no_of_obj <<" Cities Present !";  
    goto  $_WrongInput;
  }
  cout <<endl<<" Enter new data for Update the City ";  obj->getData();
  
  /* [ obj no. * single obj size = required obj ] */
  obj_loc = (obj_no - 1) * sizeof(*obj);
  file_f.seekp(obj_loc, ios::beg);
  file_f.write((char *) obj, sizeof(*obj));
  
  // At last Display the Whole Content of the File
  cout <<endl<<" FILE CONTENT AFTER MODIFY A DATA "<<endl;
  file_f.seekg(0, ios::beg);
  
  while (file_f.read((char *) obj, sizeof(*obj))){
    obj->putData();
  }
  delete obj;  obj = nullptr;
  getch();  return 0;
}

