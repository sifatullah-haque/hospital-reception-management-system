// This program is a hospital reception management system that allows the user to:
// 1. Admit a patient
// 2. Display the list of all admitted patients
// 3. Discharge a patient
// 4. Add a doctor
// 5. Display the list of all doctors
// The program uses structures to store patient and doctor information and file handling to store the data in files.





#include<stdio.h>
#include<stdlib.h>
#include<time.h>

// structure for patient information

struct patient{
    int id;
    char patientName[50];
    char patientAddress[50];
    char disease[50];
    char date[12];
}p;

// structure for doctor information

struct doctor{
    int id;
    char name[50];
    char address[50];
    char specialize[50];
    char date[12];
}d;


// file pointer to access files

FILE *fp;

int main(){

    int ch;

    while(1){
        system("cls");
        printf("<== Hospital Reception Management System ==>\n");
        printf("\n<== Created by Sifat(10), Rimi(13) and Kotha(15)==>\n\n");
        printf("1.Admit Patient\n");
        printf("2.Patient List\n");
        printf("3.Discharge Patient\n");
        printf("4.Add Doctor\n");
        printf("5.Doctors List\n");
        printf("0.Exit\n\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);

        switch(ch){
        case 0:
            exit(0);

        case 1:
            admitPatient();
            break;

        case 2:
            patientList();
            break;

        case 3:
            dischargePatient();
            break;

        case 4:
            addDoctor();
            break;

        case 5:
            doctorList();
            break;

        default:
            printf("Invalid Choice...\n\n");

        }
        printf("\n\nPress Any Key To Continue...");
        getch();
    }

    return 0;
}

// function to admit a new patient

void admitPatient(){
    char myDate[12];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    // format the date as dd/mm/yyyy

    sprintf(myDate, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon+1, tm.tm_year + 1900);

    // copy the date to the patient structure

    strcpy(p.date, myDate);

    // open the patient file in binary append mode

    fp = fopen("patient.txt", "ab");

    printf("Enter Patient id: ");
    scanf("%d", &p.id);

    printf("Enter Patient name: ");
    fflush(stdin);
    gets(p.patientName);

    printf("Enter Patient Address: ");
    fflush(stdin);
    gets(p.patientAddress);

    printf("Enter Patient Disease: ");
    fflush(stdin);
    gets(p.disease);

    printf("\nPatient Added Successfully");



    // write the patient structure to the file

    fwrite(&p, sizeof(p), 1, fp);
    fclose(fp);
}






// function to display the list of all admitted patients
void patientList(){

    system("cls");
    printf("<== Patient List ==>\n\n");
    printf("%-10s %-30s %-30s %-20s %s\n", "Id", "Patient Name", "Address", "Disease", "Date");
    printf("----------------------------------------------------------------------------------------------------------\n");

    fp = fopen("patient.txt", "rb");
    while(fread(&p, sizeof(p), 1, fp) == 1){
        printf("%-10d %-30s %-30s %-20s %s\n", p.id, p.patientName, p.patientAddress, p.disease, p.date);
    }

    fclose(fp);
}

// function to discharge a patient

void dischargePatient(){
    int id, f=0;
    system("cls");
    printf("<== Discharge Patient ==>\n\n");
    printf("Enter Patient id to discharge: ");
    scanf("%d", &id);




    FILE *ft;

    // open the patient file in binary read mode

    fp = fopen("patient.txt", "rb");

    // open a temporary file in binary write mode

    ft = fopen("temp.txt", "wb");

    while(fread(&p, sizeof(p), 1, fp) == 1){

        if(id == p.id){
                // set the flag to indicate that the patient is found
            f=1;
        }else{
            // write the patient information to the temporary file
            fwrite(&p, sizeof(p), 1, ft);
        }
    }

    if(f==1){
        printf("\n\nPatient Discharged Successfully.");
    }else{
        printf("\n\nRecord Not Found !");
    }

    fclose(fp);
    fclose(ft);

    remove("patient.txt");
    rename("temp.txt", "patient.txt");

}
// function to add a Doctor
void addDoctor(){

    char myDate[12];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(myDate, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon+1, tm.tm_year + 1900);
    strcpy(d.date, myDate);

    int f=0;

    system("cls");
    printf("<== Add Doctor ==>\n\n");

    fp = fopen("doctor.txt", "ab");

    printf("Enter Doctor id: ");
    scanf("%d", &d.id);

    printf("Enter Doctor Name: ");
    fflush(stdin);
    gets(d.name);

    printf("Enter Doctor Address: ");
    fflush(stdin);
    gets(d.address);

    printf("Doctor Specialize in: ");
    fflush(stdin);
    gets(d.specialize);

    printf("Doctor Added Successfully\n\n");

    fwrite(&d, sizeof(d), 1, fp);
    fclose(fp);
}


// function to to see doctor list
void doctorList(){
    system("cls");
    printf("<== Doctor List ==>\n\n");

    printf("%-10s %-30s %-30s %-30s %s\n", "id", "Name", "Address", "Specialize","Date");
    printf("-------------------------------------------------------------------------------------------------------------------\n");

    fp = fopen("doctor.txt", "rb");
    while(fread(&d, sizeof(d), 1, fp) == 1){
        printf("%-10d %-30s %-30s %-30s %s\n", d.id, d.name, d.address, d.specialize, d.date);
    }

    fclose(fp);
}
/*
This is a C program for a Hospital Reception Management System. The program provides various options to the user such as admitting a new patient, displaying a list of patients, discharging a patient, adding a new doctor, and displaying a list of doctors. The program uses structures to store information about patients and doctors, and uses file handling to read and write data to external files.

The program starts by displaying a menu with various options. The user can choose an option by entering the corresponding number. The program uses a switch statement to perform different tasks based on the user's choice.

The main function calls different functions for each option selected. Here is a brief description of each function:

    admitPatient(): This function adds a new patient to the system. It asks the user to enter the patient's id, name, address, disease, and current date. Then it stores the patient information in a file named "patient.txt".

    patientList(): This function displays a list of all patients in the system. It reads patient information from the "patient.txt" file and displays it on the screen in a tabular format.

    dischargePatient(): This function removes a patient from the system. It asks the user to enter the patient's id and then searches for the patient in the "patient.txt" file. If found, it removes the patient's information from the file. Otherwise, it displays an error message.

    addDoctor(): This function adds a new doctor to the system. It asks the user to enter the doctor's id, name, address, specialization, and current date. Then it stores the doctor information in a file named "doctor.txt".

    doctorList(): This function displays a list of all doctors in the system. It reads doctor information from the "doctor.txt" file and displays it on the screen in a tabular format.

The program also uses the time.h header file to get the current date and time. The program generates the current date and stores it in the patient and doctor structures when a new patient or doctor is added to the system. The program also uses the stdlib.h header file to exit the program and the conio.h header file to wait for a key press before continuing.

Note that this code has potential security vulnerabilities because it uses the unsafe functions fflush(), gets(), and scanf(). It is recommended to use the safer functions such as fgets() and scanf_s() instead.

*/
