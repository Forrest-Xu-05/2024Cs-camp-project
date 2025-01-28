#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <locale.h>
#include<unistd.h>
int check_permission(const char*file,int mode)
{
    if(access(file,mode)==0){
        return 1;
    }
    else{
        return 0;
    }
}
void show_help() {
    printf(
        "Usage of Linux commands: cp, rm, tar\n\n"
        "1. `cp` command\n"
        "`cp` is used to copy files or directories.\n\n"
        "Basic syntax:\n"
        "cp [options] source_file target_file\n\n"
        "Common options:\n"
        "- `-r` or `--recursive`: Copy directories recursively.\n"
        "- `-i` or `--interactive`: Prompt before overwriting.\n"
        "- `-v` or `--verbose`: Display detailed information.\n"
        "- `-u` or `--update`: Copy only when the source file is newer.\n\n"
        "Examples:\n"
        "- Copy a file:\n"
        "  cp file1.txt file2.txt\n"
        "- Copy a directory:\n"
        "  cp -r dir1 dir2\n"
        "- Copy and display details:\n"
        "  cp -v file1.txt file2.txt\n\n"
        "2. `rm` command\n"
        "`rm` is used to delete files or directories.\n\n"
        "Basic syntax:\n"
        "rm [options] file_or_directory\n\n"
        "Common options:\n"
        "- `-r` or `--recursive`: Delete directories recursively.\n"
        "- `-f` or `--force`: Force deletion without confirmation.\n"
        "- `-i` or `--interactive`: Prompt before deletion.\n"
        "- `-v` or `--verbose`: Display detailed information.\n\n"
        "Examples:\n"
        "- Delete a file:\n"
        "  rm file.txt\n"
        "- Delete a directory and its contents:\n"
        "  rm -r dir\n"
        "- Force delete a file without confirmation:\n"
        "  rm -f file.txt\n\n"
        "3. `tar` command\n"
        "`tar` is used to archive and extract files, often combined with compression tools.\n\n"
        "Basic syntax:\n"
        "tar [options] file_or_directory\n\n"
        "Common options:\n"
        "- `-c` or `--create`: Create a new archive.\n"
        "- `-x` or `--extract`: Extract files from an archive.\n"
        "- `-v` or `--verbose`: Display detailed information.\n"
        "- `-f` or `--file`: Specify the archive file name.\n"
        "- `-z` or `--gzip`: Use gzip compression.\n"
        "- `-j` or `--bzip2`: Use bzip2 compression.\n"
        "- `-t` or `--list`: List the contents of an archive.\n\n"
        "Examples:\n"
        "- Archive a directory:\n"
        "  tar -cvf archive.tar dir\n"
        "- Archive and compress with gzip:\n"
        "  tar -czvf archive.tar.gz dir\n"
        "- Extract a tar archive:\n"
        "  tar -xvf archive.tar\n"
        "- Extract a gzip-compressed tar archive:\n"
        "  tar -xzvf archive.tar.gz\n"
        "- List the contents of a tar archive:\n"
        "  tar -tvf archive.tar\n"
    );
}
void Copypatten(char* source,char*destination)
{
    if(access(source,F_OK)==0&&access(destination,F_OK)==0)//文件是否存在
    {
    if(!check_permission(source,R_OK)){
        printf("Error:No read permission for source file:%s\n",source);
        return ;
    }
    if(!check_permission(destination,W_OK)){
        printf("Error:No write permisson for destination file:%s\n",destination);
        return;//是否有权限
    }
    char command[100];
    snprintf(command,sizeof(command),"cp %s %s",source,destination);
    printf("Executing command:%s\n",command);
    int result =system(command );
    if(result==0){
        printf("File copied successfully:%s ->%s\n",source,destination);
    }else{
        printf("Fail to copy file.Please check the command format .\n");
    }
    }else{
            printf("Error file or destination is not exist");
        }
}
void Removepatten(char* file)
{
    if(access(file,F_OK)==0){
     if (!check_permission(file, W_OK)){
        printf("Error: No write permission for file: %s\n", file);
        return;
    }

    char command[100];
    snprintf(command, sizeof(command), "rm %s", file);
    printf("Executing command: %s\n", command);
    int result = system(command);
    if (result == 0) {
        printf("File deleted successfully: %s\n", file);
    } else {
        printf("Failed to delete file. Please check the command format.\n");
    }
    }else{
        printf("Error:file is not exist");
    }
}

// 压缩文件
void compress_files(char* archive, char* files) {
    if(access(files,F_OK)==0){
    if (!check_permission(files, R_OK)) {
        printf("Error: No read permission for files: %s\n", files);
        return;
    }

    char command[100];
    snprintf(command, sizeof(command), "tar -cvf %s %s", archive, files);
    printf("Executing command: %s\n", command);
    int result = system(command);
    if (result == 0) {
        printf("Files compressed successfully: %s\n", archive);
    } else {
        printf("Failed to compress files. Please check the command format.\n");
    }
    }else{
        printf("Erorr :files are not all existed");
    }
}
// 解压文件
void extract_files(char* archive) {
    if(access(archive,F_OK)==0){
    if (!check_permission(archive, R_OK)) {
        printf("Error: No read permission for archive: %s\n", archive);
        return;
    }

    char command[100];
    snprintf(command, sizeof(command), "tar -xvf %s", archive);
    printf("Executing command: %s\n", command);
    int result = system(command);
    if (result == 0) {
        printf("Files extracted successfully: %s\n", archive);
    } else {
        printf("Failed to extract files. Please check the command format.\n");
    }
    }else{
        printf("Erorr:archive is not existd");
    }
}
void parse_command(const char*input,char *command,char *options,char *source,char *destination)
{
    char input_copy[100];
    strncpy(input_copy,input,sizeof(input_copy));
    char *tokens[20];
    int token_count = 0;
    char *token=strtok(input_copy," ");
    while ((token!=NULL&&token_count<20))
    {
        tokens[token_count++]=token;
        token=strtok(NULL," ");
    }
command[0]='\0';
options[0]='\0';
source[0]='\0';
destination[0]='\0';
if (token_count>0)
{
    strncpy(command,tokens[0],20);
}
int i =1;
while (i<token_count)
{
    if(tokens[i][0]=='-'){
        if(strlen(options)>0)
        {
            strcat(options," ");
        }
        strcat(options,tokens[i]);
    }else{
        if(source[0]=='\0'){
            strncpy(source,tokens[i],20);
        }else if(destination[0]=='\0'){
            strncpy(destination,tokens[i],20);
        }
    }
    i++;
}
}
int main()
{
    setlocale(LC_ALL, "en_US.UTF-8");
    char input[100];
    char command[100];
    char option[100];
    char source[100];
    char destination[100];
    printf("Actions can be performe:\n' copy-cp- [options] <source> <destination>'\n' delete-rm-[options] <source>'\n'Compress and decompress-tar-[options] <source/destination>'\n");
    printf("If you want to get more detailed instructions, please enter help\n");
    printf("enter exit to end\n");
    while(1)// 循环内部没有更新directtives,会进入死循环
    {     
        fgets(input, sizeof(input), stdin); //把原本放到上面的scanf放到这里就可以解决
        input[strcspn(input, "\n")] = '\0'; //去掉换行符
        parse_command(input,command,option,source,destination);
        //测试用
        printf("command:%s\n",command);
        printf("options:%s\n",option);
        printf("source:%s\n",source);
        printf("destination:%s\n",destination);
        if(strcmp(command,"help")==0){
            show_help();
        }else if(strncmp(command,"cp",2)==0)
        {
            Copypatten(source,destination);
        }else if(strncmp(command,"rm",2)==0){
            Removepatten(source);
        }else if (strncmp(command,"tar",3)==0)
        {
            if(destination[0]=='\0'){//destination==NUll is not correct
                extract_files(source);
            }else{
                compress_files(source,destination);
            }
        } else if(strncmp(command,"exit",4)==0)
        {
            break;
        }else{
            printf("Unknown command. Enter 'help' for instructions.\n");
        }
    }// 对于输入的指令，依次匹配cp，rm，tar关键字，匹配成功进入对应的模块，将命令尝试用system函数进行执行，如果不能执行，尝试返回错误，如果都匹配失败，返回命令错误
return 0;

}