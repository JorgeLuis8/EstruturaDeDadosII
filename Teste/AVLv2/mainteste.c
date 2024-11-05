// main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "curso.c"
#include "alunos.c"
#include "disciplinas.c"
#include "matricula.c"
#include "notas.c"

void exibir_menu()
{
    printf("\n--- Menu ---\n");
    printf("1. Cadastrar novo curso\n");
    printf("2. Cadastrar novo aluno\n");
    printf("3. Cadastrar nova disciplina\n");
    printf("4. Cadastrar nova matricula\n");
    printf("5. Cadastrar Nota\n");
    printf("6. Listar alunos de um curso\n");
    printf("7. Mostrar todos os cursos\n");
    printf("8. Mostrar todas as disciplinas de um curso\n");
    printf("9. Mostrar todas as disciplinas de um determinado periodo\n");
    printf("10. Mostrar todas as disciplinas que o aluno está matriculado\n");
    printf("11. Mostrar todas as notas de disciplinas de um determinado período de um aluno\n");
    printf("12. Mostrar a nota de uma disciplina de um aluno (inclui período e carga horária)\n");
    printf("13. Remover uma disciplina de um curso (sem alunos matriculados)\n");
    printf("14. Remover uma disciplina da matrícula de um aluno\n");
    printf("15. Mostrar o histórico de um aluno\n");
    printf("0. Sair\n");
    printf("Escolha uma opcao: ");
}

int main()
{
    Arvore_curso *raiz_cursos = NULL;
    Aluno *raiz_alunos = NULL;
    int opcao = -1;
    int codigo, codigo_curso, matricula_num, carga_horaria, periodo;
    float nota;
    char nome[100], semestre_cursado[100];
    Aluno *aluno;
    Arvore_curso *curso;
    arvore_disciplinas *disciplina;

    while (opcao != 0)
    {
        exibir_menu();
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            // Solicita que o usuário digite o código do curso.
            printf("Digite o codigo do curso: ");
            scanf("%d", &codigo);

            // Verifica se já existe um curso com o mesmo código.
            if (buscar_curso(raiz_cursos, codigo) != NULL)
            {
                printf("Codigo de curso ja existente. Cadastro do curso nao realizado.\n");
                break; // Sai do switch se o código já existir.
            }

            // Solicita que o usuário digite o nome do curso.
            printf("Digite o nome do curso: ");
            scanf(" %[^\n]", nome); // Lê uma string que pode conter espaços.

            // Solicita que o usuário digite o período do curso.
            printf("Digite o periodo do curso: ");
            scanf("%d", &periodo);

            // Cria um novo curso usando a função criar_curso().
            curso = criar_curso();
            curso->codigo = codigo;    // Atribui o código informado ao novo curso.
            curso->periodo = periodo;  // Atribui o período informado ao novo curso.
            strcpy(curso->nome, nome); // Copia o nome do curso para o novo curso.

            // Insere o novo curso na árvore de cursos.
            raiz_cursos = inserir_curso(raiz_cursos, curso);
            printf("Curso cadastrado com sucesso!\n"); // Mensagem de sucesso.
            break;

        case 2:
            // Solicita ao usuário que digite a matrícula do aluno.
            printf("Digite a matricula do aluno: ");
            scanf("%d", &matricula_num);

            // Verifica se já existe um aluno com a mesma matrícula.
            if (buscar_aluno(raiz_alunos, matricula_num) != NULL)
            {
                printf("Matricula ja existente. Cadastro do aluno nao realizado.\n");
                break; // Sai do switch se a matrícula já existir.
            }

            // Solicita ao usuário que digite o nome do aluno.
            printf("Digite o nome do aluno: ");
            scanf(" %[^\n]", nome); // Lê uma string que pode conter espaços.

            // Solicita ao usuário que digite o código do curso do aluno.
            printf("Digite o codigo do curso do aluno: ");
            scanf("%d", &codigo_curso);

            // Busca o curso correspondente ao código informado.
            curso = buscar_curso(raiz_cursos, codigo_curso);
            if (curso == NULL)
            {
                printf("Codigo de curso nao encontrado. Cadastro do aluno nao realizado.\n");
                break; // Sai do switch se o curso não for encontrado.
            }

            // Cria um novo aluno usando a função criar_aluno().
            aluno = criar_aluno();
            aluno->matricula = matricula_num;   // Atribui a matrícula ao novo aluno.
            strcpy(aluno->nome, nome);          // Copia o nome do aluno.
            aluno->codigo_curso = codigo_curso; // Atribui o código do curso ao aluno.
            aluno->raiz_matriculas = NULL;      // Inicializa a raiz de matrículas como NULL.
            aluno->raiz_notas = NULL;           // Inicializa a raiz de notas como NULL.

            // Insere o novo aluno na árvore de alunos.
            raiz_alunos = inserir_aluno(raiz_alunos, aluno);
            printf("Aluno cadastrado com sucesso!\n"); // Mensagem de sucesso.
            break;

        case 3:

            // Solicita ao usuário que digite o código do curso da disciplina.
            printf("Digite o codigo do curso da disciplina: ");
            scanf("%d", &codigo_curso);

            // Busca o curso correspondente ao código informado.
            curso = buscar_curso(raiz_cursos, codigo_curso);
            if (curso == NULL)
            {
                printf("Codigo de curso nao encontrado. Cadastro da disciplina nao realizado.\n");
                break; // Sai do switch se o curso não for encontrado.
            }

            // Solicita ao usuário que digite o código da disciplina.
            printf("Digite o codigo da disciplina: ");
            scanf("%d", &codigo);

            // Verifica se já existe uma disciplina com o mesmo código.
            if (buscar_disciplina(curso->raiz_disciplinas, codigo) != NULL)
            {
                printf("Codigo de disciplina ja existente. Cadastro da disciplina nao realizado.\n");
                break; // Sai do switch se o código da disciplina já existir.
            }

            // Solicita ao usuário que digite o nome da disciplina.
            printf("Digite o nome da disciplina: ");
            scanf(" %[^\n]", nome); // Lê uma string que pode conter espaços.

            // Solicita ao usuário que digite a carga horária da disciplina.
            printf("Digite a carga horaria da disciplina: ");
            scanf("%d", &carga_horaria);

            // Valida a carga horária inserida.
            if (carga_horaria < 30 || carga_horaria > 90 || carga_horaria % 15 != 0)
            {
                printf("Carga horaria invalida. Cadastro da disciplina nao realizado.\n");
                break; // Sai do switch se a carga horária for inválida.
            }

            // Solicita ao usuário que digite o período da disciplina.
            printf("Digite o periodo da disciplina: ");
            scanf("%d", &periodo);

            // Valida o período inserido.
            if (periodo < 1 || periodo > curso->periodo)
            {
                printf("Periodo invalido. Cadastro da disciplina nao realizado.\n");
                break; // Sai do switch se o período for inválido.
            }

            // Cria um novo objeto disciplina usando a função criar_disciplina().
            disciplina = criar_disciplina();
            disciplina->codigo = codigo;               // Atribui o código da disciplina.
            strcpy(disciplina->nome, nome);            // Copia o nome da disciplina.
            disciplina->carga_horaria = carga_horaria; // Atribui a carga horária da disciplina.
            disciplina->periodo = periodo;             // Atribui o período da disciplina.

            // Insere a nova disciplina na árvore de disciplinas do curso.
            curso->raiz_disciplinas = inserir_disciplina(curso->raiz_disciplinas, disciplina);
            printf("Disciplina cadastrada com sucesso.\n"); // Mensagem de sucesso.
            break;

        case 4:

            // Solicita ao usuário que digite a matrícula do aluno.
            printf("Digite a matricula do aluno: ");
            scanf("%d", &matricula_num);

            // Busca o aluno correspondente à matrícula informada.
            aluno = buscar_aluno(raiz_alunos, matricula_num);
            if (aluno == NULL)
            {
                printf("Matricula nao encontrada.\n");
                break; // Sai do switch se a matrícula não for encontrada.
            }

            // Busca o curso do aluno a partir do código do curso armazenado no registro do aluno.
            curso = buscar_curso(raiz_cursos, aluno->codigo_curso);
            if (curso == NULL)
            {
                printf("Curso do aluno nao encontrado.\n");
                break; // Sai do switch se o curso do aluno não for encontrado.
            }

            // Solicita ao usuário que digite o código da disciplina.
            printf("Digite o codigo da disciplina: ");
            scanf("%d", &codigo);

            // Busca a disciplina correspondente ao código informado no curso do aluno.
            disciplina = buscar_disciplina(curso->raiz_disciplinas, codigo);
            if (disciplina == NULL)
            {
                printf("Disciplina nao encontrada.\n");
                break; // Sai do switch se a disciplina não for encontrada.
            }

            // Verifica se o aluno já está matriculado na disciplina.
            if (buscar_matricula(aluno->raiz_matriculas, codigo) != NULL)
            {
                printf("Disciplina já matriculada.\n");
                break; // Sai do switch se o aluno já estiver matriculado na disciplina.
            }

            // Cria uma nova matrícula para a disciplina.
            arvore_matricula *nova_matricula = criar_matricula();
            nova_matricula->codigo_disciplina = codigo; // Atribui o código da disciplina à nova matrícula.

            // Insere a nova matrícula na árvore de matrículas do aluno.
            aluno->raiz_matriculas = inserir_matriculas(aluno->raiz_matriculas, nova_matricula);
            printf("Matricula cadastrada com sucesso.\n"); // Mensagem de sucesso.
            break;

        case 5:

            // Solicita ao usuário que digite a matrícula do aluno.
            printf("Digite a matricula do aluno: ");
            scanf("%d", &matricula_num);

            // Busca o aluno correspondente à matrícula informada.
            aluno = buscar_aluno(raiz_alunos, matricula_num);
            if (aluno == NULL)
            {
                printf("Matricula nao encontrada.\n");
                break; // Sai do switch se a matrícula não for encontrada.
            }

            // Solicita ao usuário que digite o código da disciplina para cadastrar a nota.
            printf("Digite o codigo da disciplina para cadastrar a nota: ");
            scanf("%d", &codigo);

            // Verifica se o aluno está matriculado na disciplina.
            if (buscar_matricula(aluno->raiz_matriculas, codigo) == NULL)
            {
                printf("Disciplina nao matriculada pelo aluno. Cadastro da nota nao realizado.\n");
                break; // Sai do switch se o aluno não estiver matriculado na disciplina.
            }

            // Solicita informações sobre a nota.
            printf("Digite o semestre cursado: ");
            scanf("%s", semestre_cursado); // Captura o semestre em que a disciplina foi cursada.
            printf("Digite a nota da disciplina: ");
            scanf("%f", &nota); // Captura a nota final da disciplina.

            // Cria uma nova nota para a disciplina.
            arvore_notas *nova_nota = criar_nota();
            nova_nota->codigo_disciplina = codigo;                 // Atribui o código da disciplina à nova nota.
            nova_nota->nota_final = nota;                          // Atribui a nota final.
            strcpy(nova_nota->semestre_cursado, semestre_cursado); // Atribui o semestre cursado à nova nota.

            // Insere a nova nota na árvore de notas do aluno.
            aluno->raiz_notas = inserir_nota(aluno->raiz_notas, nova_nota);

            // Remove a matrícula da disciplina, já que a nota foi cadastrada.
            aluno->raiz_matriculas = remover_matricula(aluno->raiz_matriculas, codigo);

            // Mensagem de sucesso para o usuário.
            printf("Nota cadastrada com sucesso e disciplina removida das matriculas.\n");
            break;

        case 6:
            // Solicita ao usuário que digite o código do curso.
            printf("Digite o codigo do curso: ");
            scanf("%d", &codigo);

            // Busca o curso correspondente ao código informado.
            curso = buscar_curso(raiz_cursos, codigo);
            if (curso == NULL)
            {
                printf("Curso nao encontrado.\n");
                break; // Sai do switch se o curso não for encontrado.
            }

            // Exibe o nome do curso e inicia a impressão dos alunos matriculados.
            printf("Alunos do curso %s:\n", curso->nome);
            imprimir_alunos(raiz_alunos, codigo);
            break;

        case 7:

            // Verifica se a árvore de cursos está vazia
            if (raiz_cursos == NULL)
            {
                printf("Nenhum curso cadastrado.\n");
                break; // Sai do switch se não houver cursos cadastrados
            }

            // Exibe uma mensagem de cabeçalho
            printf("Cursos cadastrados:\n");

            // Chama a função para imprimir a lista de cursos
            imprimir_cursos(raiz_cursos);
            break;

        case 8:

            // Solicita ao usuário o código do curso
            printf("Digite o codigo do curso: ");
            scanf("%d", &codigo);

            // Busca o curso na árvore usando o código fornecido
            curso = buscar_curso(raiz_cursos, codigo);

            // Verifica se o curso foi encontrado
            if (curso == NULL)
            {
                printf("Curso nao encontrado.\n");
                break; // Sai do switch se o curso não for encontrado
            }

            // Exibe o nome do curso encontrado
            printf("Disciplinas do curso %s:\n", curso->nome);

            // Chama a função para imprimir as disciplinas do curso
            imprimir_disciplinas(curso->raiz_disciplinas);
            break;

        case 9:

            // Solicita ao usuário o código do curso
            printf("Digite o codigo do curso: ");
            scanf("%d", &codigo);

            // Busca o curso na árvore usando o código fornecido
            curso = buscar_curso(raiz_cursos, codigo);

            // Verifica se o curso foi encontrado
            if (curso == NULL)
            {
                printf("Curso nao encontrado.\n");
                break; // Sai do switch se o curso não for encontrado
            }

            // Solicita ao usuário o período
            printf("Digite o periodo: ");
            scanf("%d", &periodo);

            // Exibe o nome do curso e o período solicitado
            printf("Disciplinas do curso %s do periodo %d:\n", curso->nome, periodo);

            // Chama a função para imprimir as disciplinas do curso no período especificado
            imprimir_disciplinas_periodo(curso->raiz_disciplinas, periodo);
            break;

        case 10:
            // Solicita ao usuário a matrícula do aluno
            printf("Digite a matricula do aluno: ");
            scanf("%d", &matricula_num);

            // Busca o aluno na árvore usando a matrícula fornecida
            aluno = buscar_aluno(raiz_alunos, matricula_num);

            // Verifica se o aluno foi encontrado
            if (aluno == NULL)
            {
                printf("Matricula nao encontrada.\n");
                break; // Sai do switch se o aluno não for encontrado
            }

            // Exibe o nome do aluno
            printf("Disciplinas do aluno %s:\n", aluno->nome);

            // Chama a função para imprimir as disciplinas do aluno
            imprimir_matricula(aluno->raiz_matriculas);
            break;

        case 11:

            // Solicita ao usuário a matrícula do aluno
            printf("Digite a matricula do aluno: ");
            scanf("%d", &matricula_num);

            // Busca o aluno na árvore usando a matrícula fornecida
            aluno = buscar_aluno(raiz_alunos, matricula_num);

            // Verifica se o aluno foi encontrado
            if (aluno == NULL)
            {
                printf("Matricula nao encontrada.\n");
                break; // Sai do switch se o aluno não for encontrado
            }

            // Solicita ao usuário o período para o qual deseja ver as notas
            printf("Digite o periodo: ");
            scanf("%d", &periodo);

            // Verifica se o aluno tem notas cadastradas
            if (aluno->raiz_notas == NULL)
            {
                printf("Nenhuma nota cadastrada para o aluno.\n");
                break; // Sai do switch se não houver notas
            }

            // Busca as notas do aluno para o período fornecido
            nova_nota = buscar_notas(aluno->raiz_notas, periodo);

            // Verifica se foram encontradas notas para o período solicitado
            if (nova_nota == NULL)
            {
                printf("Nenhuma nota cadastrada para o aluno no periodo %d.\n", periodo);
                break; // Sai do switch se não houver notas para o período
            }

            // Exibe as notas do aluno para o período informado
            printf("Notas do aluno %s no periodo %d:\n", aluno->nome, periodo);
            imprimir_notas(nova_nota); // Imprime as notas encontradas
            break;

        case 12:

            // Solicita a matrícula do aluno
            printf("Digite a matricula do aluno: ");
            scanf("%d", &matricula_num);

            // Busca o aluno na árvore usando a matrícula fornecida
            aluno = buscar_aluno(raiz_alunos, matricula_num);

            // Verifica se o aluno foi encontrado
            if (aluno == NULL)
            {
                printf("Matricula nao encontrada.\n");
                break; // Sai do switch se o aluno não for encontrado
            }

            // Solicita o código da disciplina
            printf("Digite o codigo da disciplina: ");
            scanf("%d", &codigo);

            // Busca as notas do aluno para a disciplina fornecida
            arvore_notas *nota_busca = buscar_notas(aluno->raiz_notas, codigo);

            // Verifica se a nota foi encontrada
            if (nota_busca == NULL)
            {
                printf("Disciplina nao encontrada.\n");
                break; // Sai do switch se a disciplina não estiver matriculada
            }

            // Busca o curso do aluno usando o código do curso
            curso = buscar_curso(raiz_cursos, aluno->codigo_curso);

            // Verifica se o curso foi encontrado
            if (curso == NULL)
            {
                printf("Curso do aluno nao encontrado.\n");
                break; // Sai do switch se o curso não for encontrado
            }

            // Busca a disciplina no curso usando o código da disciplina
            disciplina = buscar_disciplina(curso->raiz_disciplinas, codigo);

            // Verifica se a disciplina foi encontrada no curso
            if (disciplina == NULL)
            {
                printf("Disciplina nao encontrada no curso.\n");
                break; // Sai do switch se a disciplina não for encontrada
            }

            // Exibe a nota do aluno na disciplina
            printf("Nota do aluno %s na disciplina %d: %.2f\n", aluno->nome, nota_busca->codigo_disciplina, nota_busca->nota_final);
            printf("Periodo: %d\n", disciplina->periodo);
            printf("Carga Horaria: %d\n", disciplina->carga_horaria);
            break;

        case 13:
            // Solicita o código do curso
            printf("Digite o codigo do curso: ");
            scanf("%d", &codigo);

            // Busca o curso usando o código fornecido
            curso = buscar_curso(raiz_cursos, codigo);

            // Verifica se o curso foi encontrado
            if (curso == NULL)
            {
                printf("Curso nao encontrado.\n");
                break; // Sai do switch se o curso não for encontrado
            }

            // Solicita o código da disciplina
            printf("Digite o codigo da disciplina: ");
            scanf("%d", &codigo);

            // Busca a disciplina a ser removida no curso
            arvore_disciplinas *disciplina_remover = buscar_disciplina(curso->raiz_disciplinas, codigo);

            // Verifica se a disciplina foi encontrada
            if (disciplina_remover == NULL)
            {
                printf("Disciplina nao encontrada.\n");
                break; // Sai do switch se a disciplina não for encontrada
            }

            // Inicializa o contador de alunos matriculados
            int alunos_matriculados = 0;

            // Itera sobre todos os alunos cadastrados
            for (Aluno *a = raiz_alunos; a != NULL; a = a->prox)
            {
                // Verifica se o aluno está matriculado na disciplina
                if (buscar_matricula(a->raiz_matriculas, codigo) != NULL)
                {
                    alunos_matriculados = 1; // Marca que há alunos matriculados
                    break;                   // Sai do loop se pelo menos um aluno estiver matriculado
                }
            }

            // Verifica se existem alunos matriculados na disciplina
            if (alunos_matriculados)
            {
                printf("Disciplina nao pode ser removida pois ha alunos matriculados.\n");
            }
            else
            {
                // Remove a disciplina do curso se não houver alunos matriculados
                curso->raiz_disciplinas = remover_disciplina(curso->raiz_disciplinas, codigo);
                printf("Disciplina removida com sucesso.\n");
            }
            break;

        case 14:

            // Solicita a matrícula do aluno
            printf("Digite a matricula do aluno: ");
            scanf("%d", &matricula_num);

            // Busca o aluno usando a matrícula fornecida
            aluno = buscar_aluno(raiz_alunos, matricula_num);

            // Verifica se o aluno foi encontrado
            if (aluno == NULL)
            {
                printf("Matricula nao encontrada.\n");
                break; // Sai do switch se o aluno não for encontrado
            }

            // Solicita o código da disciplina
            printf("Digite o codigo da disciplina: ");
            scanf("%d", &codigo);

            // Busca a matrícula da disciplina na raiz de matrículas do aluno
            arvore_matricula *matricula = buscar_matricula(aluno->raiz_matriculas, codigo);

            // Verifica se a disciplina foi encontrada na matrícula do aluno
            if (matricula == NULL)
            {
                printf("Disciplina nao encontrada na matricula do aluno.\n");
                break; // Sai do switch se a disciplina não for encontrada
            }

            // Remove a disciplina da raiz de matrículas do aluno
            aluno->raiz_matriculas = remover_matricula(aluno->raiz_matriculas, codigo);
            printf("Disciplina removida com sucesso da matricula do aluno.\n");
            break;

        case 15:

            // Solicita a matrícula do aluno
            printf("Digite a matricula do aluno: ");
            scanf("%d", &matricula_num);

            // Busca o aluno usando a matrícula fornecida
            aluno = buscar_aluno(raiz_alunos, matricula_num);

            // Verifica se o aluno foi encontrado
            if (aluno == NULL)
            {
                printf("Matricula nao encontrada.\n");
                break; // Sai do switch se o aluno não for encontrado
            }

            // Exibe o nome do aluno
            printf("Historico do aluno %s:\n", aluno->nome);

            // Chama a função para imprimir o histórico do aluno
            imprimir_historico(aluno, raiz_cursos);
            break;

        case 0:
            printf("Saindo...\n");
            break;

        default:
            printf("Opcao invalida. Tente novamente.\n");
        }
    }

    return 0;
}
