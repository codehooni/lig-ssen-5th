#include <iostream>

class Point{
			int x;
			int y;
		public:
		  Point():x(0), y(0){}
			Point(int x, int y):x(x), y(y){
				//this->x = x;
				//this->y = y;
			}
			void show(){
        std::cout << "x:" << x << ", y:" << y << std::endl;
		  }
};

int main(){
    Point *p = new Point(1, 2);//객체 한개 힙에 생성
    p->show();
    
    Point points[2];//스택에 배열 생성. 객체 2개 있음. 
    Point *arr[] = {new Point(2,3), new Point(4,5)};
    for(int i=0;i<2;i++){
        arr[i]->show();
    }

    delete p;
    for(int i = 0; i < 2; i++) {
        delete arr[i];
    }



    // last dance


    Point *arr2 = new Point[3];
    // arr2[0] =  * new Point(1, 1+2);;
    
    for(int i=0;i<3;i++){
        arr2[i] = * new Point(i, i+2);
    }

    for(int i=0;i<3;i++){
        arr2[i].show();
    }

    for(int i = 0; i < 3; i++)
        // delete arr2[i];
    delete[] arr2;

    Point **arr3 = new Point* [3];
    // arr2[0] =  * new Point(1, 1+2);;
    
    for(int i=0;i<3;i++){
        arr3[i] = new Point(i+2, i);
    }

    for(int i=0;i<3;i++){
        arr3[i]->show();
    }

    for(int i = 0; i < 3; i++)
        delete arr3[i];
    delete arr3;



    // 주소록 만들기 과제
    // 메인이 정상적으로 돌아가도록 각 함수들 구현하기


    return 0;
}