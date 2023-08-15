#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include<bits/stdc++.h>
using namespace std;


//creating node

struct node
{

    int data=0;
    struct node* left;
    struct node* right;
    int courseCode;

    node(int val)
    {

        data = val;
        left = NULL;
        right = NULL;
    }
};



class tree
{
    public:

    node *root;
    node*cur;


    tree()
    {
        root=NULL;
    }
//adding a new node
    void add(vector<int>c,vector<int>pre)
    {
        node *Node;
        //adding courses in the tree
        for(int i =0,F=0 ;i<c.size();i++)
        {
            //check if root is NULL it puts the first course as a root
            if(root==NULL)
            {

                root=new node(c[i]);
            }
            //if the root is not NULL it puts the courses as children
        else{
            Node = new node(c[i]);
            //it calls the check function to check on the prerequisites
            check(root,pre[i],F,Node);
            }
        }
    }
//puts children left or right the prerequisites
    void check(node* t,int v ,int&f,node*Node)
    {
        //if pointer is NULL or it has the inputed value
        if(t==NULL || t->data==v)
            {
                //if node pointed on isn't null
                if(t!=NULL)
                    {
                        //checks if the left node is null
                        if(t->left==NULL)
                            {
                                //puts the node in the left node
                                t->left=Node;
                            }
                            //checks if the right node is null
                        else if(t->right==NULL)
                            {
                                //puts the node in the right node
                                t->right=Node;
                            }
                            //flag f= 1
                            f=1;
                    }
                //if node pointed on is null it returns
                return;
            }
            //if flag not equal 1
        if(f!=1)
            {
                check(t->left,v,f,Node);
                check(t->right,v,f,Node);
            }
    }

//put the tree in a preorder
    void preorder(node*r)
    {
        if(r!=NULL)
            {
                r->data;
                preorder(r->left);
                preorder(r->right);
            }
    }

//function that reads input from user and it takes two string type vectors
    void userInput(vector<string>& pastCourses, vector<string>& futureCourses)
    {
        cout << "Enter the courses which you already studied \nEnter s to stop the input \n";
        string courseName;
        //put the inputed course name in the string courseName
        while(cin>>courseName)
            {
                //stops if the user inputed s
                if(courseName=="S"||courseName=="s")
                break;
                //push the inputed course names in the pastCourses vector
                pastCourses.push_back(courseName);
            }
        cout << "Enter the courses you are willing to study \nEnter s to stop the input \n";
        //put the inputed course name in the string courseName
        while(cin>>courseName)
            {
                //stops if the user inputed s
                if(courseName=="S"||courseName=="s")
                break;
                //push the inputed course names in the futureCourses vector
                futureCourses.push_back(courseName);
            }
    }




    bool findCourse(node* root, int courseCode, vector<int>& pastCodes)
    {
        if(root==NULL)
            return false;
        if(root->courseCode==courseCode)
            return true;



        if(findCourse(root->left, courseCode, pastCodes))
            return count(pastCodes.begin(), pastCodes.end(), root->courseCode);



        if(findCourse(root->right, courseCode, pastCodes))
            return count(pastCodes.begin(), pastCodes.end(), root->courseCode);



        return false;
    }




    void results(node *root, vector<string>& pastCourses, vector<string>& futureCourses)
    {
        vector<int> pastCodes;
        for(string course : pastCourses)
            {
                stringstream ss(course);
                int courseCode;
                ss>>courseCode;
                pastCodes.push_back(courseCode);
            }



        vector<string> canStudy;
        vector<string> cannotStudy;



        for(string course : futureCourses)
            {
                bool courseFound = false;
                stringstream ss(course);
                int courseCode;
                ss>>courseCode;
                if(findCourse(root, courseCode, pastCodes))
                    canStudy.push_back(course);

                else
                    cannotStudy.push_back(course);
            }
        cout<<"The following courses are OK to take: \n";
        for(string course : canStudy)
            cout<<course<<endl;



        cout<<"The following courses are CANNOT be taken: \n";
        for(string course : cannotStudy)
            cout<<course<<endl;
    }
};






int main()
{
    vector<char>v;
    vector<int>v2;
    vector<int>courses;
    vector<int>prerequisites;
    ofstream write("registration.txt");



    write<<"101Introduction to Programming,None\n";
    write<<"207Fundamental of Data Structures & Algorithms,101Introduction to Programming\n";
    write<<"311Computer Architecture,101Introduction to Programming\n";
    write<<"217Advanced Computer Programming & Concepts,207Fundamental of Data Structures & Algorithms\n";
    write<<"313Software Engineering,311Computer Architecture\n";
    write<<"415Compiler Design,311Computer Architecture\n";
    write<<"304Analysis and Design of Algorithms,217Advanced Computer Programming & Concepts\n";
    write<<"419Theory of Computing,217Advanced Computer Programming & Concepts\n";
    write<<"315Operating Systems,313Software Engineering\n";
    write<<"404Database Systems,313Software Engineering\n";





    string text;
    ifstream read("registration.txt");




    //pushes first 3 elements in a vector
    //example: in case of 207 v=[207,101]
    while (getline(read,text))
    {
    v.push_back(text[0]);
    v.push_back(text[1]);
    v.push_back(text[2]);



    for(int i=0;i<text.size();i++)
    {
    if(text[i]==',')
    {
    v.push_back(text[i+1]);
    v.push_back(text[i+2]);
    v.push_back(text[i+3]);
    }
    }
    }
    //converting strings in v to int in v2
    string tmp="";



    for (int i=0;i<v.size()+1;i++)
    {
    if (i%3==0&&i!=0){
    //if element entered is not in the file
    if(tmp.compare("Non")==0)
    {
    v2.push_back(0);
    }
    //converting it to int
    else{
    v2.push_back(stoi(tmp));
    }
    //make tmp empty
    tmp="";
    }
    //take the next element in v and put in tmp
    tmp += (char)v[i];
    }



    for (int i=0;i<v2.size()+1;i++){
    if(i%2==0){
    courses.push_back(v2[i]);
    }
    else{
    prerequisites.push_back(v2[i]);
    }
    }

    tree t ;
    t.add(courses,prerequisites);
    t.preorder(t.root);
    vector<string> pastCourses;
    vector<string> futureCourses;
    t.userInput(pastCourses, futureCourses);
    cout<<"Processing...\n";
    t.results(t.root, pastCourses, futureCourses);
    return 0;
}
