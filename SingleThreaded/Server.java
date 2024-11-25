import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;

public class Server{
     public void run() throws IOException{
        int port = 8010;
        try {
            ServerSocket socket = new ServerSocket(port);
            socket.setSoTimeout(10000); // timeout at 10 sec
            while (true) {
                System.out.println("Server is listening on port" + port);
                Socket acceptedconnection=socket.accept();
                System.out.println("connection accepted" + acceptedconnection.getRemoteSocketAddress());
                PrintWriter toClient=new PrintWriter(acceptedconnection.getOutputStream());
                // this will give the input stream
                BufferedReader fromClient=new BufferedReader(new InputStreamReader(acceptedconnection.getInputStream()));
                toClient.println("Hello from the server");
                toClient.close();
                fromClient.close();
                acceptedconnection.close();
                socket.close();
            }
        } catch (IOException e) {
            System.out.println("IOException occurred: " + e.getMessage());
            e.printStackTrace();
        }
    }


    public static void main(String[] args) {
        Server server=new Server();
        try{
            server.run();
        }catch(Exception e){
            e.printStackTrace();
        }

    }
}