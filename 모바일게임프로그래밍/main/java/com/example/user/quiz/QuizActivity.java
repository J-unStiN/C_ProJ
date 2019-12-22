package com.example.user.quiz;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.RadioButton;
import android.widget.RadioGroup;
import android.widget.TextView;

public class QuizActivity extends AppCompatActivity {

    private String nickname;
    private String level;
    private String question = "1+1=";
    private String answer = "2";
    private String userAnswer="";

    private TextView textViewNickname;
    private TextView textViewScore;
    private TextView textViewQuiz;
    private EditText editTextAnswer;
    private RadioGroup radioGroupEx;
    private RadioButton ex1;
    private RadioButton ex2;
    private RadioButton ex3;

    private void initWidgets(){
        textViewNickname = findViewById(R.id.textViewNickname);
        textViewScore = findViewById(R.id.textViewScore);
        textViewQuiz = findViewById(R.id.textViewQuiz);
        editTextAnswer = findViewById(R.id.editTextAnswer);
        radioGroupEx = findViewById(R.id.radioGroupEx);
        ex1 = findViewById(R.id.radioButtonEx1);
        ex2 = findViewById(R.id.radioButtonEx2);
        ex3 = findViewById(R.id.radioButtonEx3);
    }
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_quiz);

        initWidgets();

        Intent intent = getIntent();
        nickname = intent.getStringExtra("nickname");
        level = intent.getStringExtra("level");

        if(nickname != null)
            textViewNickname.setText(nickname);
        textViewScore.setText("Score:0");
        textViewQuiz.setText(question);

        if(level == null)
            level = "Easy";

        if(level.equals("Easy")){
            editTextAnswer.setVisibility(View.GONE);
            ex1.setText("1");
            ex2.setText("2");
            ex3.setText("3");
        } else {
            radioGroupEx.setVisibility(View.GONE);
        }
    }

    public void onOK(View view){
        if(level.equals("Hard"))
            userAnswer = editTextAnswer.getText().toString();

        if(userAnswer.equals(answer))
            textViewScore.setText("Score:1");
    }

    public void onRadioAnswer(View view){
        RadioButton button = (RadioButton)view;
        userAnswer = button.getText().toString();
    }
}
