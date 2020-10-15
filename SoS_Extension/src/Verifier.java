import java.io.*;
import java.util.*;

public class Verifier {
    public Boolean verifyLog(String txtdir, String nof, String property, int threshold) {
        boolean ret = false;

        switch(property) {
            case "operationTime":
                ret = operationTimeVerification(txtdir, threshold);

                // CSV generation for tendency analysis of the verification property success rate
//                File file2 = new File(System.getProperty("user.dir") + "/examples/platoon_SoS/results/" + "time_" + threshold + ".csv");
//                System.out.println(System.getProperty("user.dir") + "/examples/platoon_SoS/results/"+ "time_" + threshold + ".csv");
//                FileWriter writer2 = null;
//                try {
//                    writer2 = new FileWriter(file2, true);
////                    writer.write("operationSuccessRate for " + txtdir.replace(System.getProperty("user.dir") + "/StarPlateS/SoS_Extension/", "") + " is " + Boolean.toString(ret) + "\n");
//                    writer2.write(txtdir.replace(System.getProperty("user.dir") + "/examples/platoon_SoS/results/", "") + "," + Boolean.toString(ret) + "\n");
//                    writer2.flush();
//                } catch(IOException e) {
//                    e.printStackTrace();
//                } finally {
//                    try {
//                        if(writer2 != null) writer2.close();
//                    } catch(IOException e) {
//                        e.printStackTrace();
//                    }
//                }
//                System.out.println(ret);
                break;

            case "operationSuccessRate":
                ret = operationSuccessRateVerification(txtdir, nof, threshold);

                // CSV generation for tendency analysis of the verification property success rate
//                File file = new File(System.getProperty("user.dir") + "/StarPlateS/SoS_Extension/Verification_Results" + nof + "_" + threshold + ".csv");
//                FileWriter writer = null;
//                try {
//                    writer = new FileWriter(file, true);
//                    writer.write(txtdir.replace(System.getProperty("user.dir") + "/StarPlateS/SoS_Extension/", "") + "," + Boolean.toString(ret) + "\n");
//                    writer.flush();
//                } catch(IOException e) {
//                    e.printStackTrace();
//                } finally {
//                    try {
//                        if(writer != null) writer.close();
//                    } catch(IOException e) {
//                        e.printStackTrace();
//                    }
//                }
                break;
        }

        return ret;
    }

    /* Distnace Checker Implementation */

    public Boolean verifyLog(String txtdir_plt, String txtdir_veh, String nof, String property, int threshold) {
        boolean ret = false;

        switch(property) {
            case "distanceChecker":
                ret = DistanceVerification(txtdir_plt, txtdir_veh, threshold);
                break;
        }
        return ret;
    }

    private Boolean DistanceVerification(String txtdir_plt, String txtdir_veh, int threshold) {
        boolean ret = true;

        BufferedReader reader_plt = null;
        BufferedReader reader_veh = null;
        ArrayList<Message> message_plt = new ArrayList<>();
        ArrayList<Message> message_veh = new ArrayList<>();

        try {

            reader_veh = new BufferedReader(new FileReader(new File(txtdir_veh)));

            String line;
            String startEnd;
            String vehId;
            float time;
            float distance;

            while ((line = reader_plt.readLine()) != null) {

                StringTokenizer st = new StringTokenizer(line, "\t ");

                if (st.countTokens() == 10) {
                    String temp = st.nextToken();
                    if(temp.equals("index")) continue;
                    time = Float.valueOf(st.nextToken());
                    vehId = st.nextToken();
                    st.nextToken();//lane
                    st.nextToken();//lanepos
                    st.nextToken();//speed
                    st.nextToken();//timegapsetting
                    st.nextToken();//timegap
                    distance = Float.valueOf(st.nextToken());

                    Message msg_veh = new Message();
                    msg_veh.time = time;
                    msg_veh.senderPltId = vehId;
                    msg_veh.distance = distance;
                    message_veh.add(msg_veh);
                }
            }
            reader_veh.close();

        }
        catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }

        int currentIndex = -1;

        try {
            reader_plt = new BufferedReader(new FileReader(new File(txtdir_plt)));

            String line;
            int index;
            float time;
            String vehId;

            while ((line = reader_plt.readLine()) != null) {

                StringTokenizer st = new StringTokenizer(line, "\t ");

                if (st.countTokens() == 9) {
                    String temp = st.nextToken();
                    if(temp.equals("index")) continue;

                    index = Integer.valueOf(temp);
                    time = Float.valueOf(st.nextToken());
                    vehId = st.nextToken();
                    st.nextToken();//pltMode
                    st.nextToken();//pltId
                    st.nextToken();//pltDepth
                    st.nextToken();//pltSize
                    st.nextToken();//pltOptSize
                    st.nextToken();//pltMaxSize

                    if(index != currentIndex) {

                        // Have data of previous vehicles group, calculate distance difference
                        if(message_plt.size() > 0) {
                            float totalDiff[] = new float[message_plt.size()-1];
                            for(int i = 1; i < message_plt.size(); i++) {
                                float diff = message_plt.get(i).distance - message_plt.get(i-1).distance;
                                totalDiff[i-1] = diff;
                            }

                            for(int i = 1; i < totalDiff.length; i++) {
                                if((totalDiff[i] - totalDiff[i-1]) > threshold)
                                    ret = false;
                            }
                        }

                        // Prepare For New Group
                        message_plt = new ArrayList<>();
                        currentIndex = index;
                    }

                    float distance = 0.0f;

                    // Map with vehicle distance
                    for(int i = 0; i < message_veh.size(); i++) {
                        if(message_veh.get(i).time.equals(time)
                                && message_veh.get(i).senderPltId.equals(vehId)) {
                            distance = message_veh.get(i).distance;
                            message_veh.remove(i);
                        }
                    }

                    Message msg_plt = new Message();
                    msg_plt.time = time;
                    msg_plt.senderPltId = vehId;
                    msg_plt.distance = distance;
                    message_plt.add(msg_plt);
                }
            }

            reader_plt.close();

        }
        catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
        return ret;
    }

    /* Distnace Checker Implementation */

    private Boolean operationTimeVerification(String txtdir, int threshold) {
        boolean ret = true;

        BufferedReader reader = null;
        try {
            reader = new BufferedReader(new FileReader(new File(txtdir)));

            String line;
            String startEnd;
            String vehId;
            String rcvPltId;
            float time;
            ArrayList<Message> messages = new ArrayList<>();

            while ((line = reader.readLine()) != null) {

                StringTokenizer st = new StringTokenizer(line, "\t ");

                if (st.countTokens() == 9) {
                    String temp = st.nextToken();
                    if(temp.equals("timeStep")) continue;

                    time = Float.valueOf(temp);
                    vehId = st.nextToken();
                    st.nextToken();//fromState
                    st.nextToken();//toState
                    st.nextToken();//commandSent
                    st.nextToken();//rcvId
                    st.nextToken();//senderId
                    rcvPltId = st.nextToken();
                    startEnd = st.nextToken();

                    if(startEnd.contains("Start")) {
                        Message msg = new Message();
                        msg.time = time;
                        msg.commandSent = startEnd.split("_")[0];
                        msg.senderPltId = vehId;
                        messages.add(msg);
                    } else if (startEnd.contains("End")) {
                        for(int i = 0; i < messages.size(); i++) {
                            switch(startEnd.split("_")[0]) {
                                case "Split":
                                    if(messages.get(i).commandSent.equals(startEnd.split("_")[0])
                                            && messages.get(i).senderPltId.equals(rcvPltId)) {
                                        if(time - messages.get(i).time > threshold) ret = false;
                                        else ret = true;
                                        messages.remove(i);
                                    }
                                    break;
                                default:
                                    if(messages.get(i).commandSent.equals(startEnd.split("_")[0])
                                            && messages.get(i).senderPltId.equals(vehId)) {
                                        if(time - messages.get(i).time > threshold) ret = false;
                                        else ret = true;
                                        messages.remove(i);
                                    }
                                    //ret = true; // For analyzing specific operation
                                    break;
                            }

                        }
                    }
                }
            }

            reader.close();

        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }

        return ret;
    }

    private Boolean operationSuccessRateVerification(String txtdir, String nof, int threshold) {
        boolean ret = true;
        ArrayList<Message> messages = new ArrayList<>();
        int addCount = 0;
        int delCount = 0;

        BufferedReader reader = null;
        try {
            reader = new BufferedReader(new FileReader(new File(txtdir)));

            String line;
            String command1;
            String command2;
            String senderPltId;
            String rcvId;
            String vehId;
            float time;

            while ((line = reader.readLine()) != null) {

                StringTokenizer st = new StringTokenizer(line, "\t ");

                if (st.countTokens() == 9) {
                    String temp = st.nextToken();
                    if(temp.equals("timeStep")) continue;

                    time = Float.valueOf(temp);
                    vehId = st.nextToken();
                    st.nextToken();
                    st.nextToken();
                    command1 = st.nextToken();
                    rcvId = st.nextToken();
                    senderPltId = st.nextToken();
                    st.nextToken();
                    command2 = st.nextToken();

                    if(command1.contains("REQ")) {
                        Message msg = new Message();
                        msg.receiverId = rcvId;
                        msg.senderPltId = senderPltId;
                        msg.commandSent = command1.split("_")[0];
                        messages.add(msg);
                        addCount++;
                        continue;
                    } if(command2.contains("Start")) {
                        Message msg = new Message();
                        if(senderPltId.equals("-") || rcvId.equals("-")) continue;
                        msg.commandSent = command2.split("_")[0];
                        msg.senderPltId = senderPltId;
                        msg.receiverId = rcvId;
                        messages.add(msg);
                        addCount++;
                    }

                    if (command2.contains("End")) {
                        switch(command2.split("_")[0]) {
                            case "Split":
                                for(int i = 0; i < messages.size(); i++) {
                                    if (messages.get(i).commandSent.toLowerCase().equals("split")
                                            && messages.get(i).senderPltId.equals(rcvId) && messages.get(i).receiverId.equals(senderPltId)) {
                                        messages.remove(i);
                                        delCount++;
                                        break;
                                    }
                                }
                                break;
                            case "Merge":
                                for(int i = 0; i < messages.size(); i++) {
                                    if (messages.get(i).commandSent.equals("MERGE") && messages.get(i).receiverId.equals(rcvId)) {
                                        messages.remove(i);
                                        delCount++;
                                        break;
                                    }
                                }
                                break;
                            default:
                                for(int i = 0; i < messages.size(); i++) {
                                    if (messages.get(i).commandSent.equals(command2.split("_")[0])
                                            && messages.get(i).senderPltId.equals(vehId)) {
                                        messages.remove(i);
                                        delCount++;
                                        break;
                                    }
                                }
                                break;

                        }
                    }
                }
            }

            for(int i = 0; i <messages.size(); i++) {
//                System.out.println(messages.get(i).commandSent);
            }
//            System.out.println(delCount/addCount);
            if(delCount < addCount * threshold/100) ret = false;

            reader.close();

        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }

        return ret;
    }
}
