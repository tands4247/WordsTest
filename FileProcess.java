import java.util.Scanner;
import java.io.*;


public class FileProcess{
    
    Test[] test = new Test[100];         //Test型のオブジェクト配列
    String[] dummys = new String[100];  //ダミーデータ配列
    String dummy;
    
    public void dummy_input() throws IOException{
        //ダミーデータ入力。ダミーデータのSring配列作成
        try{
            BufferedReader br = new BufferedReader(new FileReader("dummy.txt"));
            dummy = br.readLine();
            int a = 0;
            while(dummy != null){
                dummys[a] = dummy;
                a++;
                dummy = br.readLine();
            }
            br.close();
        }
        catch(IOException e){
            System.out.println("ダミーファイルが読み込めません");
        }
    }

    public void tango_input() throws IOException {
        //英語と対になる日本語を入力。都度、Test型オブジェクトを作成しテスト開始

        File fp = new File("tango.txt");
        try(Scanner sc = new Scanner(fp)){
            sc.useDelimiter(",");   //,区切り
            
            System.out.println("何問テストしますか？");
            BufferedReader br = new BufferedReader( new InputStreamReader(System.in));
            String str = br.readLine();
            int test_c = Integer.parseInt(str);     //テスト数
            
            int b= 0;
            while(sc.hasNextLine()){
                String english = sc.next();
                String japanese = sc.next();
                    
                if(b == test_c){
                    break;
                }
                test[b] = new Test(english, japanese, dummys);
                test[b].test_start(a);
                b++;
                    
                System.out.println("英語：" + english+ "  日本語:" +japanese);
                System.out.print('\n');
                sc.nextLine();  //次の行へ
            }
            
        }catch(FileNotFoundException e){
            System.out.println("ファイルが開けません");
        }
    
    }
}