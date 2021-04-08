#!/bin/bash
while read line; do
RESULT_MINISHELL=$(echo -e $line | ../minishell)
EXIT_MS=$?
VAR_MS=$(exit | ../minishell)
RESULT_BASH=$(echo -e $line | bash)
EXIT_BASH=$?
VAR_MS=$(exit | bash)
# EXIT_BASH=$(echo -e "\"\$?\" ; exit" | bash)
# echo $RESULT_MINISHELL; echo $RESULT_BASH
# echo $EXIT_MS; echo $EXIT_BASH
if [ "$RESULT_MINISHELL" == "$RESULT_BASH" ]
then
    echo "OK!"
else
{
    echo $line
    echo "NOT OKAY!"
    echo $RESULT_MINISHELL; echo $RESULT_BASH
}  
fi

# if [ "$EXIT_MS" == "$EXIT_BASH" ]
# then
#     echo "exit val OK!"
# else
# {
#     echo $line
#     echo "exit val NOT OKAY!"
#     echo $EXIT_MS echo ; echo $EXIT_BASH
# }   
# fi
# done <$1

# #!/bin/bash
# chmod +x ms_test.sh
# while read line; do
# RESULT_MINISHELL=$(echo $line; "; echo \$?; echo exit" | ../minishell)
# RESULT_BASH=$(echo $line "; echo \$?; echo exit" | bash)
# # echo $RESULT_MINISHELL; echo $RESULT_BASH
# if [ "$RESULT_MINISHELL" == "$RESULT_BASH" ]
# then
#     echo "OK!"
# else
#     echo "NOT OKAY!"
# fi
# done <$1

# #!/bin/bash
# chmod +x ms_test.sh
# while read line; do
# RESULT_MINISHELL=$(echo $line "; exit" | ../minishell)
# EXIT_MS=$(echo "\"\$?\"" | ../minishell)
# RESULT_BASH=$(echo $line "; exit" | bash)
# EXIT_BASH=$(echo "\"\$?\"" | bash)
# echo $RESULT_MINISHELL; echo $RESULT_BASH
# if [ "$RESULT_MINISHELL" == "$RESULT_BASH" ]
# then
#     echo "OK!"
# else
#     echo "NOT OKAY!"
# fi

# if [ "$EXIT_MS" == "$EXIT_BASH" ]
# then
#     echo "exit val OK!"
# else
# {
#     echo "exit val NOT OKAY!"
#     echo $EXIT_MS; echo $EXIT_BASH
# }   
# fi
# RESULT_MINISHELL=$(echo "exit" | ../minishell)
# RESULT_BASH=$(echo "exit" | bash)
# done <$1





# #!/bin/bash
# chmod +x ms_test.sh
# while read line; do
# RESULT_MINISHELL=$(echo $line  "; echo \"\$?\"; exit" | ../minishell)
# RESULT_BASH=$(echo $line  "; echo \"\$?\"; exit" | bash)
# echo $RESULT_MINISHELL; echo $RESULT_BASH
# if [ "$RESULT_MINISHELL" == "$RESULT_BASH" ]
# then
#     echo "OK!"
# else
#     echo "NOT OKAY!"
# fi
done <$1