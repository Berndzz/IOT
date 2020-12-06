import 'package:flutter/material.dart';
import 'package:mini_project_04/SceneMonitor.dart';

void main()=> runApp(MyApp());

class MyApp extends StatelessWidget{
  const MyApp({Key key}) : super (key: key);


  @override
  Widget build(BuildContext context) {
    // TODO: implement build
    return MaterialApp(
        routes: <String,WidgetBuilder>{
          'SceneMonitor' : (BuildContext context) => sceneMonitor(),
        },
        title: 'Flutter Demo',
      debugShowCheckedModeBanner: false,
      home: sceneMonitor(),
    );
  }
}