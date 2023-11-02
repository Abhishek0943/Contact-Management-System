#include <stdio.h>
#include <string.h>

struct Contact {
  int id;
  char name[50];
  char phone[15];
  char email[50];
  char address[100];
};

void addContact(struct Contact *contacts, int *count, int *nextId) {
  struct Contact newContact;
  newContact.id = (*nextId)++;

  printf("Enter Name: ");
  scanf("%s", newContact.name);
  printf("Enter Phone: ");
  scanf("%s", newContact.phone);
  printf("Enter Email: ");
  scanf("%s", newContact.email);
  printf("Enter Address: ");
  scanf("%s", newContact.address);

  contacts[(*count)++] = newContact;

  FILE *file = fopen("contacts.txt", "a");
  fprintf(file, "%d %s %s %s %s\n", newContact.id, newContact.name,
          newContact.phone, newContact.email, newContact.address);
  fclose(file);

  printf("Contact added successfully!\n");
}

void listContacts(struct Contact *contacts, int count) {
  if (count == 0) {
    printf("No contacts found.\n");
    return;
  }

  printf("Contact List:\n");
  for (int i = 0; i < count; i++) {
    printf("ID: %d\nName: %s\nPhone: %s\nEmail: %s\nAddress: %s\n\n",
           contacts[i].id, contacts[i].name, contacts[i].phone,
           contacts[i].email, contacts[i].address);
  }
}

int findContactIndex(struct Contact *contacts, int count, int id) {
  for (int i = 0; i < count; i++) {
    if (contacts[i].id == id) {
      return i;
    }
  }
  return -1;
}

void updateContact(struct Contact *contacts, int *count) {
  int id;
  printf("Enter the ID of the contact you want to update: ");
  scanf("%d", &id);

  int index = findContactIndex(contacts, *count, id);
  if (index == -1) {
    printf("Contact not found.\n");
    return;
  }

  int choice;
  printf("Select the field to update:\n");
  printf("1. Name\n");
  printf("2. Phone\n");
  printf("3. Email\n");
  printf("4. Address\n");
  printf("Enter your choice: ");
  scanf("%d", &choice);

  switch (choice) {
  case 1:
    printf("Enter the new name: ");
    scanf("%s", contacts[index].name);
    break;
  case 2:
    printf("Enter the new phone: ");
    scanf("%s", contacts[index].phone);
    break;
  case 3:
    printf("Enter the new email: ");
    scanf("%s", contacts[index].email);
    break;
  case 4:
    printf("Enter the new address: ");
    scanf("%s", contacts[index].address);
    break;
  default:
    printf("Invalid choice. No changes were made.\n");
  }

  FILE *file = fopen("contacts.txt", "w");
  for (int i = 0; i < *count; i++) {
    fprintf(file, "%d %s %s %s %s\n", contacts[i].id, contacts[i].name,
            contacts[i].phone, contacts[i].email, contacts[i].address);
  }
  fclose(file);

  printf("Contact updated successfully!\n");
}

void deleteContact(struct Contact *contacts, int *count) {
  int id;
  printf("Enter the ID of the contact you want to delete: ");
  scanf("%d", &id);

  int index = findContactIndex(contacts, *count, id);
  if (index == -1) {
    printf("Contact not found.\n");
    return;
  }

  for (int i = index; i < *count - 1; i++) {
    contacts[i] = contacts[i + 1];
  }

  (*count)--;

  FILE *file = fopen("contacts.txt", "w");
  for (int i = 0; i < *count; i++) {
    fprintf(file, "%d %s %s %s %s\n", contacts[i].id, contacts[i].name,
            contacts[i].phone, contacts[i].email, contacts[i].address);
  }
  fclose(file);

  printf("Contact deleted successfully!\n");
}

int main() {
  struct Contact contacts[100];
  int count = 0;
  int nextId = 1;

  FILE *file = fopen("contacts.txt", "r");
  if (file) {
    while (fscanf(file, "%d %s %s %s %s", &contacts[count].id,
                  contacts[count].name, contacts[count].phone,
                  contacts[count].email, contacts[count].address) != EOF) {
      count++;
      if (contacts[count - 1].id >= nextId) {
        nextId = contacts[count - 1].id + 1;
      }
    }
    fclose(file);
  }

  int choice;

  while (1) {
    printf("\nContact Management System\n");
    printf("1. Add Contact\n");
    printf("2. Update Contact\n");
    printf("3. Delete Contact\n");
    printf("4. List Contacts\n");
    printf("5. Exit\n");

    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
      addContact(contacts, &count, &nextId);
      break;
    case 2:
      updateContact(contacts, &count);
      break;
    case 3:
      deleteContact(contacts, &count);
      break;
    case 4:
      listContacts(contacts, count);
      break;
    case 5:
      printf("Goodbye!\n");
      return 0;
    default:
      printf("Invalid choice. Please try again.\n");
    }
  }

  return 0;
}
