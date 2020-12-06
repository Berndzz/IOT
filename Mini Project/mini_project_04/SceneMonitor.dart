import 'package:flutter/material.dart';
import 'package:firebase_database/firebase_database.dart';
import 'package:flutter/services.dart';

class sceneMonitor extends StatefulWidget {
  @override
  _sceneMonitorState createState() => _sceneMonitorState();
}

class _sceneMonitorState extends State<sceneMonitor> {
  @override
  final dbRef = FirebaseDatabase.instance.reference();

  Widget build(BuildContext context) {
    SystemChrome.setPreferredOrientations([
      DeviceOrientation.portraitUp,
      DeviceOrientation.portraitDown,
    ]);
    return Scaffold(
      appBar: new AppBar(
        title: Text('Esp 32 Monitor',),
        backgroundColor: Colors.green,
      ),
      body: StreamBuilder(
        stream: dbRef.child("data").onValue,
        builder: (context, snapshot) {
          if (snapshot.hasData && !snapshot.hasError && snapshot.data.snapshot.value != null) {
            return Column(
              children: [
                SizedBox(
                  height: 20,
                ),
                Row(
                  mainAxisAlignment: MainAxisAlignment.center,
                  children: [
                    Column(
                      children: [
                        Padding(
                          padding: const EdgeInsets.all(8.0),
                          child: Text(
                            "Temperature",
                            style:
                            TextStyle(
                                fontSize: 20, fontWeight: FontWeight.bold),
                          ),

                        ),
                        Padding(
                          padding: const EdgeInsets.all(8.0),
                          child: Text(
                            snapshot.data.snapshot.value['temperature'].toString() + "°C",
                            // dummy value
                            style:
                            TextStyle(
                                fontSize: 20, fontWeight: FontWeight.bold,),
                          ),
                        ),
                      ],
                    )
                  ],
                ),
                SizedBox(
                  height: 20,
                ),
                Column(
                  children: [
                    Padding(
                      padding: const EdgeInsets.all(8.0),
                      child: Text(
                        "Humidity",
                        style: TextStyle(
                            fontSize: 20, fontWeight: FontWeight.bold),
                      ),
                    ),
                    Padding(
                      padding: const EdgeInsets.all(8.0),
                      child: Text(
                        snapshot.data.snapshot.value['humidity'].toString() + "%", // dummy value
                        style: TextStyle(
                            fontSize: 20, fontWeight: FontWeight.bold),
                      ),
                    ),
                  ],
                ),
                SizedBox(
                  height: 20,
                ),
                Column(
                  children: [
                    Padding(
                      padding: const EdgeInsets.all(8.0),
                      child: Text(
                        "Distance",
                        style: TextStyle(
                            fontSize: 20, fontWeight: FontWeight.bold),
                      ),
                    ),
                    Padding(
                      padding: const EdgeInsets.all(8.0),
                      child: Text(
                        snapshot.data.snapshot.value['distance'].toString() + " cm", // dummy value
                        style: TextStyle(
                            fontSize: 20, fontWeight: FontWeight.bold),
                      ),
                    ),
                  ],
                ),
              ],
            );
          }else {
             return Container();
          }
        }),
    );
  }
}
